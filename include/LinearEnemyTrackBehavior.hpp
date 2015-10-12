#ifndef LINEARTRACKBEHAVIOR_HPP
#define LINEARTRACKBEHAVIOR_HPP
#include "EnemyTrackBehavior.hpp"
class LinearEnemyTrackBehavior : public EnemyTrackBehavior {
    virtual sf::Vector2f track(sf::Vector2f enemyPos, sf::Vector2f playerPos);
};
#endif
