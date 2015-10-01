#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/System/Vector2.hpp>

class Enemy {
    public:
        sf::Vector2f position;
        sf::Vector2f direction;    
    
        Enemy();
};
#endif
