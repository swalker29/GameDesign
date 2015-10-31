#ifndef PROJECTILEINSTANCE_HPP
#define PROJECTILEINSTANCE_HPP

#include <SFML/System/Vector2.hpp>

class ProjectileInstance {
    public:
        int projectileIndex;
        sf::Vector2f position;
        sf::Vector2f direction;
        
        ProjectileInstance(int projectileIndex, sf::Vector2f position, sf::Vector2f direction);
        
        // Default destructor
};
#endif
