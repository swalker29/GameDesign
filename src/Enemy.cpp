#include "Enemy.hpp"
#include "Game.hpp"
#include <iostream>

Enemy::Enemy() : position(0, 0), direction(0, 0), speed(0.0f), node(NULL) , stationary(false) {

}
TrackNode Enemy::track(const Game& state, const sf::Vector2f& target) {
    if (!this->trackBehavior || this->stationary) {
        TrackNode tn;
        tn.node = 0;
        tn.direction = sf::Vector2f(0,0);
        return tn;
    }

    //165
    std::shared_ptr<PathVertex> targetNode = state.level.pathVertices[168];
    TrackNode tn = this->trackBehavior->track(state, this->position, target, this->node, targetNode);

    if (this->node && this->node == targetNode) {
        tn.direction = sf::Vector2f(0,0);
        return tn;
    }

    debugTracking(tn, targetNode);

    return tn;

#if 0
    if (this->node && this->node == targetNode) {
        //track player within hierachy
        return;
    }
    
    this->direction = tn.direction;
    if (tn.node) this->node = tn.node;

    this->position.y -= this->speed * this->direction.y;
    this->position.x -= this->speed * this->direction.x;
    //std::cout << this->node->position.x << "," << this->node->position.y << " ";
    //std::cout << targetNode->position.x << "," << targetNode->position.y << std::endl;
#endif
}
void Enemy::debugTracking(TrackNode& tn, PathVertexP targetNode) {
    std::cout << this->node->position.x << "," << this->node->position.y << " ";
    std::cout << tn.node->position.x << "," << tn.node->position.y << " ";
    std::cout << targetNode->position.x << "," << targetNode->position.y << " ";
    std::cout << "(" << this->position.x << "," << this->position.y << ")";

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
