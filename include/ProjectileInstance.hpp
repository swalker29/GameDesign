#ifndef PROJECTILEINSTANCE_HPP
#define PROJECTILEINSTANCE_HPP

#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>

#include "ICollidable.hpp"

class ProjectileInstance : public ICollidable {
    public:
        int projectileIndex;
        sf::Vector2f position;
        sf::Vector2f direction; // this might not be needed
        
        bool collided;
        
        b2Body* b2body;
        b2Fixture* b2fixture;
        
        
        ProjectileInstance(int projectileIndex, sf::Vector2f position, sf::Vector2f direction, b2CircleShape* b2circleShape, b2World* b2world);
        
        // Default destructor
};
#endif
