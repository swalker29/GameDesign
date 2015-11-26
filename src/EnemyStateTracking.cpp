#include "EnemyStateTracking.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include <iostream>
#include "Utils.hpp"

#define DEBUGTRACKING 0

EnemyStateTracking::EnemyStateTracking() {}

#if DEBUGTRACKING
void debugTracking(TrackNode& tn, PathVertexP targetNode, const sf::Vector2f& target, Enemy& enemy);
#endif
void EnemyStateTracking::handle(const Game& state, Enemy& enemy) {
    //enemy.track(state);
    TrackNode tn;
    PathVertexP targetNode = state.player.node;
    sf::Vector2f target = state.player.position;
    if (!enemy.trackBehavior || enemy.stationary) {
        tn.node = enemy.node;
        tn.direction = sf::Vector2f(0,0);
    } else if (enemy.node && enemy.node == targetNode) { 
        sf::Vector2f direction = target - enemy.position;
        normalizeVector2f(direction);
        tn.direction = direction;

        tn = enemy.fallbackBehavior->track(state, enemy.position, target, enemy.node, targetNode);
    } else {
        tn = enemy.trackBehavior->track(state, enemy.position, target, enemy.node, targetNode);
    }

#if DEBUGTRACKING
    debugTracking(tn, targetNode, target, enemy);
#endif
    enemy.tracking = tn;
}
#if DEBUGTRACKING
void debugTracking(TrackNode& tn, PathVertexP targetNode, const sf::Vector2f& target, Enemy& enemy) {
    std::cout << enemy.node->position.x << "," << enemy.node->position.y << " ";
    std::cout << tn.node->position.x << "," << tn.node->position.y << " ";
    std::cout << targetNode->position.x << "," << targetNode->position.y << " ";
    std::cout << "(" << enemy.position.x << "," << enemy.position.y << ")" << " ";
    std::cout.precision(2);
    std::cout << "(" <<  target.x << "," << target.y << ")";

    std::cout << std::endl;
}
#endif
