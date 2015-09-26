#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System/Vector2.hpp>

class Player {
    public:
        sf::Vector2f position;
        sf::Vector2f direction;    
    
        Player();
};
#endif
