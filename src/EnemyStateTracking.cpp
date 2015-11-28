#include "EnemyStateTracking.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include <iostream>
#include "Utils.hpp"

#define DEBUGTRACKING 1

EnemyStateTracking::EnemyStateTracking(EnemyTrackBehavior& etb)
    : trackBehavior(&etb) {}

void EnemyStateTracking::setTransition(std::shared_ptr<EnemyState> onDest) {
    this->onDest = onDest;
}

#if DEBUGTRACKING
void debugTracking(TrackNode& tn, PathVertexP targetNode, const sf::Vector2f& target, Enemy& enemy);
#endif

void EnemyStateTracking::handle(Game& state, Enemy& enemy) {
#if 0
    if (!enemy.trackBehavior || enemy.stationary) {
        tn.node = enemy.node;
        tn.direction = sf::Vector2f(0,0);
    }
#endif
    PathVertexP targetNode = state.player.node;
    TrackNode tn;

    if (enemy.node && enemy.node == targetNode && this->onDest) {
        tn.node = enemy.node;
        tn.direction = sf::Vector2f(0,0);
        enemy.tracking = tn;

        enemy.state = this->onDest;
        return;
    }

    sf::Vector2f target = state.player.position;
    tn = this->trackBehavior->track(state, enemy.position, target, enemy.node, targetNode);
    enemy.tracking = tn;
#if DEBUGTRACKING
    debugTracking(tn, targetNode, target, enemy);
#endif

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
