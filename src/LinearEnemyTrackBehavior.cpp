#include "LinearEnemyTrackBehavior.hpp"
#include "Utils.hpp"

sf::Vector2f LinearEnemyTrackBehavior::track(sf::Vector2f enemyPos, sf::Vector2f playerPos) {
    sf::Vector2f newVec = enemyPos - playerPos;
    normalizeVector2f(newVec);
    return newVec;
}
