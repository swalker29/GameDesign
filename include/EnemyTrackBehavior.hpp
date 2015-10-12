#ifndef ENEMYTRACKBEHAVIOR_HPP
#define ENEMYTRACKBEHAVIOR_HPP
#include <SFML/System/Vector2.hpp>
class EnemyTrackBehavior {
public:
    virtual sf::Vector2f track(sf::Vector2f enemyPos, sf::Vector2f playerPos)=0;
};
#endif
