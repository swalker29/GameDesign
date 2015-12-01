#ifndef ASTARENEMYTRACKBEHAVIOR_HPP
#define ASTARENEMYTRACKBEHAVIOR_HPP
#include "EnemyTrackBehavior.hpp"
#include <random>
class AStarEnemyTrackBehavior : public EnemyTrackBehavior {
    private:
        std::default_random_engine rgen;
    public:
        virtual TrackNode track(const Game& state, const sf::Vector2f& myPos, const sf::Vector2f& playerPos, PathVertexP myNode, PathVertexP destNode);
};
#endif
