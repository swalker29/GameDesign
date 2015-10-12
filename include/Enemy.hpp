#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/System/Vector2.hpp>
#include "LinearEnemyTrackBehavior.hpp"
class Enemy {
    private:
        EnemyTrackBehavior* trackBehavior;
    public:
        static LinearEnemyTrackBehavior linearTrackBehavior;
        sf::Vector2f position;
        sf::Vector2f direction;    
        float speed;
        void track(sf::Vector2f playerPos);
        void setTrackBehavior(EnemyTrackBehavior& newTrackBehavior);
        Enemy();
};
#endif
