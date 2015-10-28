#include "Game.hpp"
#include <string>
#include <cstdio>
#include "TrackingEnemyFactory.hpp"

static const std::string LEVEL_FILE = "assets/map.level";

static constexpr float32 BOX2D_TIMESTEP = 1.0f / 60.0f;
static constexpr int32 BOX2D_VELOCITY_ITERATIONS = 8; // suggested default
static constexpr int32 BOX2D_POSITION_ITERATIONS = 3; // suggested default
static constexpr float32 BOX2D_VOID_DENSITY = 0.0f;

Game::Game() : b2world(b2Vec2(0.0f, 0.0f)) {

}

// Default destructor

bool Game::init() {
    
    if (!level.init(LEVEL_FILE, &this->meshPoints)) {
        return false;
    }

    NavEdge ne;
    ne.from = &this->meshPoints.front();
    ne.to = &this->meshPoints.back();
    ne.weight = 1.0;
    this->meshEdges.push_back(ne);

    const int nEnemies = 10;
    sf::Vector2f start(0.5, 0);
    sf::Vector2f direction(0,1);
    float speed = 0.01;

    TrackingEnemyFactory linearEF(TrackingEnemyFactory::AStarTrackBehavior);

    for (int i=0; i < nEnemies; i++) {
        std::unique_ptr<Enemy> enemy = linearEF.makeEnemyAt(start, direction, speed);
        start.x += 0.15;
        enemy->setNode(this->meshPoints.front());
        this->enemies.push_back(std::move(enemy));
    }
    
    initBox2D();
    
    return true;
}

void Game::update(const float timeElapsed, InputData& input) {
    // get actions from input
    player.position += 0.13f * input.movement;
    
    if (input.aim.x != 0 || input.aim.y != 0) {
        player.direction = input.aim;
    }
    
    // all the real game logic starts here
    for (auto& enemy : enemies) {
        enemy->track(*this, player.position);
    }
        
    // update the box2d entities based on where player and enemies want to go
    //player.b2body->SetTransform(b2Vec2(player.position.x, player.position.y), 0.0f);
    //player.b2body->ApplyForce(b2Vec2(input.movement.x, input.movement.y), player.b2body->GetPosition(), true);
    giveImpulseToBody(player.b2body, 7.13f * input.movement);
    
    b2world.Step(BOX2D_TIMESTEP, BOX2D_VELOCITY_ITERATIONS, BOX2D_POSITION_ITERATIONS);
    b2world.ClearForces();
    b2Vec2 position = player.b2body->GetPosition();
    player.position.x = position.x;
    player.position.y = position.y;
    
    // box2d creation and destroying of collision entities for nearby tiles
    // sounds wasteful but there's no better way
}

void Game::initBox2D() {
    b2BodyDef bodyDef; 
    bodyDef.type = b2_dynamicBody; 
    bodyDef.position.Set(0.0f, 0.0f); // TODO: set to the player's starting location
    player.b2body = b2world.CreateBody(&bodyDef);
    // might need to create a fixture def later on
    player.b2fixture = player.b2body->CreateFixture(&player.circle, 1.0f); // player has density of 1.0. Don't think this will be important.
    
    // TODO: only add tiles that are neccessary instead of all tiles
    for (int x = 0; x < level.width; x++) {
        for (int y = 0; y < level.height; y++) {
            addTileElementToWorld(x, y);
        }
    }
    
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
