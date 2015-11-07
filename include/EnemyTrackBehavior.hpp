#ifndef ENEMYTRACKBEHAVIOR_HPP
#define ENEMYTRACKBEHAVIOR_HPP
#include <SFML/System/Vector2.hpp>
#include <memory>
#include "PathVertex.hpp"
#define TRACKNODE_EPISLON 0.015

class Game;

typedef struct TrackNode {
    std::shared_ptr<PathVertex> node;
    sf::Vector2f direction;
} TrackNode;

class EnemyTrackBehavior {
public:
    virtual TrackNode track(const Game& state, const sf::Vector2f& myPos, const sf::Vector2f& playerPos, PathVertexP myNode, PathVertexP destNode)=0;
};
#endif
