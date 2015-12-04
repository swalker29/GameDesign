#include "Game.hpp"

#include <cstdio>
#include <random>
#include <string>

#include "EnemyStateFiring.hpp"
#include "EnemyStatePouncing.hpp"
#include "TrackingEnemyFactory.hpp"
#include "Utils.hpp"

static const std::string LEVEL_FILE_PATH = "assets/map.level";
static const std::string WEAPONS_FILE_PATH = "assets/weapons.wep";
static const std::string PROJECTILES_FILE_PATH = "assets/projectiles.proj";

static constexpr float32 BOX2D_TIMESTEP = 1.0f / 60.0f;
static constexpr int32 BOX2D_VELOCITY_ITERATIONS = 8; // suggested default
static constexpr int32 BOX2D_POSITION_ITERATIONS = 3; // suggested default
static constexpr float32 BOX2D_VOID_DENSITY = 0.0f;

static constexpr float FAR_AWAY_ENEMY_THRESHOLD = (Game::TILE_SIZE * 6.0f) * (Game::TILE_SIZE * 6.0f); // 6 tiles away
static constexpr int KILL_BONUS = 10;
static constexpr int MAX_ENEMIES_SPAWNED = 35;
static constexpr int AMMO_SCORE_INTERVAL = 250;
static constexpr float HEALTH_REGEN_RATE = 0.004f;
static constexpr float SPAWN_TIME_INTERVAL = 3.0f;

static constexpr float BLUE_ENEMY_RADIUS = 0.25f;
static constexpr float ORANGE_ENEMY_RADIUS = 0.5f;
static constexpr float RED_ENEMY_RADIUS = 1.0f;

std::list<sf::Sound> Game::playingSounds;


// TODO: find a better home for these
static TrackingEnemyFactory meleeEF(TrackingEnemyFactory::AStarTrackBehavior, std::shared_ptr<EnemyStateClose> (new EnemyStateTracking(TrackingEnemyFactory::LinearTrackBehavior)));
static TrackingEnemyFactory rangedEF(TrackingEnemyFactory::AStarTrackBehavior, std::shared_ptr<EnemyStateClose> (new EnemyStateFiring));
static TrackingEnemyFactory pounceEF(TrackingEnemyFactory::AStarTrackBehavior, std::shared_ptr<EnemyStateClose> (new EnemyStatePouncing));


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
    
    for (int x = 0; x < weapons.size(); x++) {
        player.ammoCounts.push_back(0);
    }
    
    player.addAmmo();
    player.position = level.startingPosition * TILE_SIZE;
    
    nextAmmoRefil = AMMO_SCORE_INTERVAL;

    PathVertexP enemyStart = this->level.pathVertices[205];
    sf::Vector2f direction(0,0);
    float speed = 2.5;
    static std::default_random_engine rgen;
    std::uniform_real_distribution<float> sVar(-1.5, 1.5);

    spawnClock.restart();
    spawnWaveClock.restart();
    
    initBox2D();
    
    return true;
}

void Game::update(const float timeElapsed, InputData& input) {
    // get actions from input
    player.node = this->level.findClosestNode(player.position);
    
    if (input.aim.x != 0.0f || input.aim.y != 0.0f) {
        player.direction = input.aim;
    }
    if (input.movement.x != 0.0f || input.movement.y != 0.0f) {
        player.movementDirection = input.movement;
    }
    
    player.activeWeapon += input.weaponChange;
    if (player.activeWeapon == -1) {
        player.activeWeapon = weapons.size() - 1;
    }
    else if (player.activeWeapon >= weapons.size()) {
        player.activeWeapon = 0;
    }
    
    float playerMaxHealth = Player::PLAYER_MAX_HEALTH;
    player.health = std::min(playerMaxHealth, player.health + HEALTH_REGEN_RATE);

    //update the score based on time elapsed.
    score += timeElapsed;
    spawnThreshold += timeElapsed;
    if(score >= 100) {
        score += timeElapsed;
        spawnThreshold += timeElapsed;
    } else if (score >= 250) {
        score += timeElapsed * 2;
        spawnThreshold += timeElapsed * 2;
    } else if (score >= 500) {
        score += timeElapsed * 3;
        spawnThreshold += timeElapsed * 3;
    } else if (score >= 1000) {
        score += timeElapsed * 4;
        spawnThreshold += timeElapsed * 4;
    } else if (score >= 2000) {
        score += timeElapsed * 5;
        spawnThreshold += timeElapsed * 5;
    } else if (score >= 4000) {
        score += timeElapsed * 6;
        spawnThreshold += timeElapsed * 6;
    } else if (score >= 6000) {
        score += timeElapsed * 7;
        spawnThreshold += timeElapsed * 7;
    } else if (score >= 8000) {
        score += timeElapsed * 8;
        spawnThreshold += timeElapsed * 8;
    }

    sf::Time curTime = spawnClock.getElapsedTime();
    //spawn a number of spiders every seven seconds, increases as score increases.
    if (curTime.asSeconds() > SPAWN_TIME_INTERVAL) {
        spawnClock.restart();
        int randEnemy = rand() % 3 + 1; //generates int between 1 and 3
        float tempScore = score / 100;
        int enemyCountModulo = int(tempScore + 0.5) + 1;
        int enemyCount = (rand() % enemyCountModulo) + 1;

        float speedShift = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float speed = 1.5 + speedShift;
        
        int xSpawnModifier = 1;
        int xSpawnRand = rand() % 2 + 1;
        if (xSpawnRand == 2) { xSpawnModifier = -1; }
        int ySpawnModifier = 1;
        int ySpawnRand = rand() % 2 + 1;
        if (ySpawnRand == 2) { ySpawnModifier = -1; }
        
        for(int i = 0; i < enemyCount; i++) {
            spawnEnemy(randEnemy);
        }
    }
    
    // all the real game logic starts here
    for (auto& enemy : enemies) {
        enemy->action(*this);
        TrackNode tn = enemy->tracking;
        enemy->node = cmpVector2f(enemy->position, tn.node->position, 0.015) ? tn.node : enemy->node;
        sf::Vector2f box2dV = enemy->speed * tn.direction;
        enemy->direction = tn.direction;
        giveImpulseToBody(enemy->b2body, box2dV);
    }
    
    if (input.fireWeapon && (player.activeWeapon == Game::CHAINSAW_INDEX || player.ammoCounts[player.activeWeapon] > 0)) {
        bool fired = weapons[player.activeWeapon].fire(player, &projectiles, &projectileInstances, &enemies, &b2world);
        
        if (fired) {
            player.ammoCounts[player.activeWeapon]--;
        }
    }
        
    // update the box2d entities based on where player and enemies want to go
    giveImpulseToBody(player.b2body, 7.13f * input.movement);
    
    b2world.Step(BOX2D_TIMESTEP, BOX2D_VELOCITY_ITERATIONS, BOX2D_POSITION_ITERATIONS);
    b2world.ClearForces();
    
    // update all of the positions of player, enemies, and projectiles
    b2Vec2 playerPosition = player.b2body->GetPosition();
    player.oldPosition = player.position;
    player.position.x = playerPosition.x;
    player.position.y = playerPosition.y;
    player.distanceTraveled += distanceSquared(player.oldPosition, player.position);
    
    for (auto iter = enemies.begin(); iter != enemies.end(); iter++) {
        b2Vec2 position = (*iter)->b2body->GetPosition();
        (*iter)->oldPosition = (*iter)->position;
        (*iter)->position.x = position.x;
        (*iter)->position.y = position.y;
        (*iter)->distanceTraveled += distanceSquared((*iter)->oldPosition, (*iter)->position);
        
        // if enemy is dead, add points to the score
        if ((*iter)->health <= 0.0f) {
            score += KILL_BONUS;
        }
        
        // if enemy has ran out of health or is very far away, remove it
        float distanceSq = distanceSq = distanceSquared(player.position, (*iter)->position);
        
        if ((*iter)->health <= 0.0f || distanceSq > FAR_AWAY_ENEMY_THRESHOLD) {
            (*iter)->b2body->DestroyFixture((*iter)->b2fixture);
            b2world.DestroyBody((*iter)->b2body);
            enemies.erase(iter--);
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
    
    // add ammo if the player passed the score target
    if (score >= nextAmmoRefil) {
        player.addAmmo();
        nextAmmoRefil += AMMO_SCORE_INTERVAL;
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

void Game::spawnEnemy(int attackType) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<float> offsetDist(-Game::TILE_SIZE + 1.0f, Game::TILE_SIZE - 1.0f);
    static std::uniform_int_distribution<int> tileDist(-3, 3);

    if (enemies.size() >= MAX_ENEMIES_SPAWNED) {
        return;
    }

    bool foundTile = false;
    
    int x = 0;
    int y = 0;
    
    sf::Vector2i playerTile = getPlayerTile();
    
    while (!foundTile) {
        int xOffset = tileDist(mt);
        int yOffset = tileDist(mt);
        
        if (xOffset == 0 && yOffset == 0) {
            continue;
        }
        
        x = std::max(0, std::min(playerTile.x + xOffset, level.width - 1));
        y = std::max(0, std::min(playerTile.y + yOffset, level.height - 1));
        
        if (!level.tileVector[level.tiles[x][y].resource].hasCollision) {
            foundTile = true;
        }
    }
    
    sf::Vector2f spawnLocation = tileCenter(x, y, Game::TILE_SIZE);
    sf::Vector2f direction = player.position - spawnLocation;
    
    PathVertexP enemyStart = level.pathVertices[x*level.width + y];
    
    std::unique_ptr<Enemy> enemy;
    
    switch(attackType) {
        case 1:
            enemy = rangedEF.makeEnemyAt(enemyStart, direction, 1.0f);
            enemy->circle.m_radius = ORANGE_ENEMY_RADIUS;
        break;
        case 2:
            enemy = meleeEF.makeEnemyAt(enemyStart, direction, 2.0f);
            enemy->circle.m_radius = RED_ENEMY_RADIUS;
        break;
        case 3 :
            enemy = pounceEF.makeEnemyAt(enemyStart, direction, 2.5f);
            enemy->circle.m_radius = BLUE_ENEMY_RADIUS;
        break;
        default:
            enemy = rangedEF.makeEnemyAt(enemyStart, direction, 2.0f);
            enemy->circle.m_radius = ORANGE_ENEMY_RADIUS;
        break;
    }
    
    enemy->position += sf::Vector2f(offsetDist(mt), offsetDist(mt));
    enemy->attackType = attackType;    
    createEnemyBox2D(*enemy);
    enemies.push_back(std::move(enemy));
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
