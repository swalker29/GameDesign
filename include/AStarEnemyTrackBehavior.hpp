#ifndef ASTARENEMYTRACKBEHAVIOR_HPP
#define ASTARENEMYTRACKBEHAVIOR_HPP
#include "EnemyTrackBehavior.hpp"
class AStarEnemyTrackBehavior : public EnemyTrackBehavior {
    virtual TrackNode track(const Game& state, const sf::Vector2f& node, const sf::Vector2f& myPos, const sf::Vector2f& playerPos);
};
#endif
