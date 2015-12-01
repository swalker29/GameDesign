#ifndef ASTARENEMYTRACKBEHAVIOR_HPP
#define ASTARENEMYTRACKBEHAVIOR_HPP
#include "EnemyTrackBehavior.hpp"
class AStarEnemyTrackBehavior : public EnemyTrackBehavior {
    private:
#if 0
        std::default_random_engine rgen;
#endif
    public:
        virtual TrackNode track(const Game& state, const sf::Vector2f& myPos, const sf::Vector2f& playerPos, PathVertexP myNode, PathVertexP destNode);
};
#endif
