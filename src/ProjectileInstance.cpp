#include "ProjectileInstance.hpp"

ProjectileInstance::ProjectileInstance(int projectileIndex, sf::Vector2f position, sf::Vector2f direction, b2CircleShape* b2circleShape, b2World* b2world) : projectileIndex(projectileIndex), position(position), direction(direction) {
    b2BodyDef bodyDef; 
    bodyDef.type = b2_dynamicBody; 
    bodyDef.bullet = true;
    bodyDef.position.Set(position.x, position.y); // TODO: set to the player's starting location
    b2body = b2world->CreateBody(&bodyDef);
    
    b2fixture = b2body->CreateFixture(b2circleShape, 0.0001f); // set density to really low so bullets don't push enemies around
}

// Default destructor