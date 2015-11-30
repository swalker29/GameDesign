#include "Game.hpp"
#include <string>
#include <cstdio>
#include "Utils.hpp"
#include "TrackingEnemyFactory.hpp"
#include "EnemyStateFiring.hpp"
#include "EnemyStatePouncing.hpp"
#include <random>

static const std::string LEVEL_FILE_PATH = "assets/map.level";
static const std::string WEAPONS_FILE_PATH = "assets/weapons.wep";
static const std::string PROJECTILES_FILE_PATH = "assets/projectiles.proj";

static constexpr float32 BOX2D_TIMESTEP = 1.0f / 60.0f;
static constexpr int32 BOX2D_VELOCITY_ITERATIONS = 8; // suggested default
static constexpr int32 BOX2D_POSITION_ITERATIONS = 3; // suggested default
static constexpr float32 BOX2D_VOID_DENSITY = 0.0f;

std::list<sf::Sound> Game::playingSounds;

Game::Game() : b2world(b2Vec2(0.0f, 0.0f)), player(&b2world), contactListener(&projectiles, &enemies, player) {

}

// Default destructor

bool Game::init() {
    
    if (!level.init(LEVEL_FILE_PATH)) {
        fprintf(stderr, "Error: Unable to import level file: %s\n", LEVEL_FILE_PATH.c_str());
        return false;
    }
    
    if (!Projectile::importProjectiles(PROJECTILES_FILE_PATH, &projectiles)) {
        fprintf(stderr, "Error: Unable to import projectiles file: %s\n", PROJECTILES_FILE_PATH.c_str());
        return false;
    }
    
    if (!Weapon::importWeapons(WEAPONS_FILE_PATH, &weapons, projectiles.size())) {
        fprintf(stderr, "Error: Unable to import weapons file: %s\n", WEAPONS_FILE_PATH.c_str());
        return false;
    }
    
    player.position = level.startingPosition * TILE_SIZE;

    PathVertexP enemyStart = this->level.pathVertices[205];
    sf::Vector2f direction(0,0);
    float speed = 1.5;
    std::default_random_engine rgen;
    std::uniform_real_distribution<float> sVar(-0.5, 0.5);

    TrackingEnemyFactory meleeEF(TrackingEnemyFactory::AStarTrackBehavior, std::shared_ptr<EnemyStateClose> (new EnemyStateTracking(TrackingEnemyFactory::LinearTrackBehavior)));

    TrackingEnemyFactory rangedEF(TrackingEnemyFactory::AStarTrackBehavior, std::shared_ptr<EnemyStateClose> (new EnemyStateFiring));

    TrackingEnemyFactory pounceEF(TrackingEnemyFactory::AStarTrackBehavior, std::shared_ptr<EnemyStateClose> (new EnemyStatePouncing));

    const int rangedEnemies = 1;
    for (int i=0; i < rangedEnemies; i++) {
        std::unique_ptr<Enemy> enemy = rangedEF.makeEnemyAt(enemyStart, direction, speed + sVar(rgen));
        createEnemyBox2D(*enemy);
        this->enemies.push_back(std::move(enemy));
    }
    const int meleeEnemies = 0;
    for (int i=0; i < meleeEnemies; i++) {
        std::unique_ptr<Enemy> enemy = meleeEF.makeEnemyAt(enemyStart, direction, speed + sVar(rgen));
        createEnemyBox2D(*enemy);
        this->enemies.push_back(std::move(enemy));
    }
    const int pounceEnemies = 1;
    for (int i=0; i < pounceEnemies; i++) {
        std::unique_ptr<Enemy> enemy = pounceEF.makeEnemyAt(enemyStart, direction, speed + sVar(rgen));
        createEnemyBox2D(*enemy);
        this->enemies.push_back(std::move(enemy));
    }
    
    initBox2D();
    
    return true;
}

void Game::update(const float timeElapsed, InputData& input) {
    // get actions from input
    player.position += 0.13f * input.movement;
    player.node = this->level.findClosestNode(player.position);
    
    if (input.aim.x != 0 || input.aim.y != 0) {
        player.direction = input.aim;
    }
    
    player.activeWeapon += input.weaponChange;
    if (player.activeWeapon == -1) {
        player.activeWeapon = weapons.size() - 1;
    }
    else if (player.activeWeapon >= weapons.size()) {
        player.activeWeapon = 0;
    }

	//update the score based on time elapsed.
	score += timeElapsed;
	if(score >= 100) {
		score += timeElapsed;
	} else if (score >= 500) {
		score += timeElapsed * 2;
	} else if (score >= 1500) {
		score += timeElapsed * 3;
	} else if (score >= 3000) {
		score += timeElapsed * 4;
	} else if (score >= 5000) {
		score += timeElapsed * 5;
	} else if (score >= 10000) {
		score += timeElapsed * 6;
	}
    
    // all the real game logic starts here
    for (auto& enemy : enemies) {
        enemy->action(*this);
        TrackNode tn = enemy->tracking;
        enemy->node = cmpVector2f(enemy->position, tn.node->position, 0.015) ? tn.node : enemy->node;
        sf::Vector2f box2dV = enemy->speed * tn.direction;
        giveImpulseToBody(enemy->b2body, box2dV);
    }
    
    if (input.fireWeapon) {
        weapons[player.activeWeapon].fire(player, &projectiles, &projectileInstances, &enemies, &b2world);
    }
        
    // update the box2d entities based on where player and enemies want to go
    giveImpulseToBody(player.b2body, 7.13f * input.movement);
    
    b2world.Step(BOX2D_TIMESTEP, BOX2D_VELOCITY_ITERATIONS, BOX2D_POSITION_ITERATIONS);
    b2world.ClearForces();
    
    // update all of the positions of player, enemies, and projectiles
    b2Vec2 playerPosition = player.b2body->GetPosition();
    player.position.x = playerPosition.x;
    player.position.y = playerPosition.y;
    
    for (auto iter = enemies.begin(); iter != enemies.end(); iter++) {
        b2Vec2 position = (*iter)->b2body->GetPosition();
        (*iter)->position.x = position.x;
        (*iter)->position.y = position.y;
        
        // if enemy has ran out of health, remove it
        if ((*iter)->health <= 0.0f) {
            (*iter)->b2body->DestroyFixture((*iter)->b2fixture);
            b2world.DestroyBody((*iter)->b2body);
            enemies.erase(iter--);
			score += 10; //add 10 to score, should change.
        }
    }
    
    for (auto iter = projectileInstances.begin(); iter != projectileInstances.end(); iter++) {        
        b2Vec2 position = (*iter)->b2body->GetPosition();
        (*iter)->position.x = position.x;
        (*iter)->position.y = position.y;
        
        // if collision, delete object
        if ((*iter)->collided) {
            (*iter)->b2body->DestroyFixture((*iter)->b2fixture);
            b2world.DestroyBody((*iter)->b2body);
            projectileInstances.erase(iter--);
        }
    }
    
    // check for finished sounds and remove them. Just check 5-10 sounds per frame
    int count = 0;
    for (auto iter = playingSounds.begin(); iter != playingSounds.end() && count < 10; iter++) {
        if ((*iter).getStatus() == sf::Sound::Stopped) {
            playingSounds.erase(iter--);
        }
        count++;
    }
        
    
    // box2d creation and destroying of collision entities for nearby tiles
    // sounds wasteful but there's no better way
}

void Game::playSound(const sf::SoundBuffer& buffer) {
    playingSounds.push_back(sf::Sound());
    playingSounds.back().setBuffer(buffer);
    playingSounds.back().play();   
}

void Game::initBox2D() {
    player.b2body->SetTransform(b2Vec2(player.position.x, player.position.y), player.b2body->GetAngle());
    
    // TODO: only add tiles that are neccessary instead of all tiles
    for (int x = 0; x < level.width; x++) {
        for (int y = 0; y < level.height; y++) {
            addTileElementToWorld(x, y);
        }
    }
    
    b2world.SetContactListener(&contactListener);
}

void Game::createEnemyBox2D(Enemy& enemy) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(enemy.position.x, enemy.position.y);
    enemy.b2body = b2world.CreateBody(&bodyDef);
    enemy.b2fixture = enemy.b2body->CreateFixture(&enemy.circle, 1.0f);
    enemy.b2fixture->SetUserData(&enemy);
}

void Game::giveImpulseToBody(b2Body* b2body, sf::Vector2f desiredVelocity) {
    b2Vec2 currentVelocity = b2body->GetLinearVelocity();

    b2Vec2 desiredChange(desiredVelocity.x - currentVelocity.x, desiredVelocity.y - currentVelocity.y);
    b2Vec2 impulse = b2body->GetMass() * desiredChange;
    b2body->ApplyLinearImpulse(impulse, b2body->GetWorldCenter(), true);
}

void Game::addTileElementToWorld(int x, int y) {
    if (level.tileVector[level.tiles[x][y].resource].hasCollision) {
        b2BodyDef bodyDef; // static body by default
        
        if (level.tiles[x][y].b2body != nullptr) {
            removeTileElementFromWorld(x, y);
        }
        
        int rotation = level.tiles[x][y].rotation;
        float additionalX = rotation > 0 && rotation < 3 ? TILE_SIZE : 0.0f;
        float additionalY = rotation > 1 ? TILE_SIZE : 0.0f;
              
        bodyDef.position.Set(x * TILE_SIZE + additionalX, y * TILE_SIZE + additionalY);
        bodyDef.angle = level.tiles[x][y].rotation * b2_pi / 2.0f;
        
        level.tiles[x][y].b2body = b2world.CreateBody(&bodyDef);
        level.tiles[x][y].b2fixture = level.tiles[x][y].b2body->CreateFixture(&(level.tileVector[level.tiles[x][y].resource].shape), BOX2D_VOID_DENSITY);
        if (!level.tileVector[level.tiles[x][y].resource].projectilesCollide) {
            b2Filter filter;
            filter.groupIndex = -2;
            level.tiles[x][y].b2fixture->SetFilterData(filter);
        }
    }
}

void Game::removeTileElementFromWorld(int x, int y) {
    if (level.tileVector[level.tiles[x][y].resource].hasCollision) {
        level.tiles[x][y].b2body->DestroyFixture(level.tiles[x][y].b2fixture);    
        b2world.DestroyBody(level.tiles[x][y].b2body);
        level.tiles[x][y].b2body = nullptr;
        level.tiles[x][y].b2fixture = nullptr;
    }
}
