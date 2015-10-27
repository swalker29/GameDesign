#ifndef ENEMYTRACKBEHAVIOR_HPP
#define ENEMYTRACKBEHAVIOR_HPP
#include <SFML/System/Vector2.hpp>

#define TRACKNODE_EPISLON 0.015

class Game;

typedef struct TrackNode {
    const sf::Vector2f* node;
    sf::Vector2f direction;
} TrackNode;

class EnemyTrackBehavior {
public:
    virtual TrackNode track(const Game& state, const sf::Vector2f& node, const sf::Vector2f& myPos, const sf::Vector2f& playerPos)=0;
};
#endif
