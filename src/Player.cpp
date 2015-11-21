#include "Player.hpp"

static constexpr float PLAYER_COLLISION_RADIUS = 0.5f; // Box2D units so in meters
static constexpr float PLAYER_MAX_HEALTH = 100.0f;

Player::Player(b2World* b2world) : Character(PLAYER_MAX_HEALTH, Character::Team::HUMAN), position(0.0f, 0.0f), direction(1.0f, 0.0f) {
    circle.m_p.Set(0.0f, 0.0f);
    circle.m_radius = PLAYER_COLLISION_RADIUS;
    
    b2BodyDef bodyDef; 
    bodyDef.type = b2_dynamicBody; 
    bodyDef.position.Set(position.x, position.y);
    b2body = b2world->CreateBody(&bodyDef);
    // might need to create a fixture def later on
    b2fixture = b2body->CreateFixture(&circle, 1.0f); // player has density of 1.0. Don't think this will be important.
    b2fixture->SetUserData(this);
}

// Default destructor

