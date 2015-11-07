#ifndef LINEARTRACKBEHAVIOR_HPP
#define LINEARTRACKBEHAVIOR_HPP
#include "EnemyTrackBehavior.hpp"
class LinearEnemyTrackBehavior : public EnemyTrackBehavior {
    virtual TrackNode track(const Game& state, const sf::Vector2f& myPos, const sf::Vector2f& playerPos, PathVertexP myNode, PathVertexP destNode);
};
#endif
