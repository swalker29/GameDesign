#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>

#include "Character.hpp"
#include "PathVertex.hpp"

class Player : public Character{
    public:
        static constexpr float PLAYER_MAX_HEALTH = 100.0f;
    
        sf::Vector2f position;
        sf::Vector2f direction; 
        PathVertexP node;
        
        // for animation
        sf::Vector2f oldPosition;
        float distanceTraveled;
        sf::Vector2f movementDirection;
        
        b2Body* b2body;
        b2Fixture* b2fixture;
        b2CircleShape circle;
        
        int activeWeapon;
        std::vector<int> ammoCounts;
        
        Player(b2World* b2world);
        
        void addAmmo();
};
#endif
