#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>

class Player {
    public:
        sf::Vector2f position;
        sf::Vector2f direction; 
        
        b2Body* b2body;
        b2Fixture* b2fixture;
        b2CircleShape circle;
    
        Player();
};
#endif
