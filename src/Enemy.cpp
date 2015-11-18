#include "Enemy.hpp"
#include "EnemyStateMelee.hpp"
#include "EnemyStateTracking.hpp"
#include "Game.hpp"
#include <iostream>
#include "Utils.hpp"

Enemy::Enemy() : position(0, 0), direction(0, 0), speed(0.0f), node(NULL) , stationary(false) {

}
void Enemy::track(const Game& state, const sf::Vector2f& target) {
    if (!this->trackBehavior || this->stationary) {
        TrackNode tn;
        tn.node = 0;
        tn.direction = sf::Vector2f(0,0);
        this->tracking = tn;
    }

    //165
    //std::shared_ptr<PathVertex> targetNode = state.level.pathVertices[168];
    PathVertexP targetNode = state.level.findClosestNode(target);
    TrackNode tn;

    tn = this->trackBehavior->track(state, this->position, target, this->node, targetNode);

    if (this->node && this->node == targetNode) {
        sf::Vector2f direction = target - this->position;
        normalizeVector2f(direction);
        tn.direction = direction;
    }

    //debugTracking(tn, targetNode, target);
    this->tracking = tn;
}
void Enemy::debugTracking(TrackNode& tn, PathVertexP targetNode, const sf::Vector2f& target) {
    std::cout << this->node->position.x << "," << this->node->position.y << " ";
    std::cout << tn.node->position.x << "," << tn.node->position.y << " ";
    std::cout << targetNode->position.x << "," << targetNode->position.y << " ";
    std::cout << "(" << this->position.x << "," << this->position.y << ")" << " ";
    std::cout.precision(2);
    std::cout << "(" <<  target.x << "," << target.y << ")";

    std::cout << std::endl;
}
void Enemy::setTrackBehavior(EnemyTrackBehavior& newBehavior) {
    this->trackBehavior = &newBehavior;
}

void Enemy::setNode(PathVertexP newNode) {
    this->node = newNode;
    this->position.y = this->node->position.y;
    this->position.x = this->node->position.x;
}
