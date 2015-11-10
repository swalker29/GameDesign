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

    std::shared_ptr<PathVertex> targetNode = state.level.pathVertices[4];
    TrackNode tn = this->trackBehavior->track(state, this->position, target, this->node, targetNode);

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
void Enemy::setTrackBehavior(EnemyTrackBehavior& newBehavior) {
    this->trackBehavior = &newBehavior;
}

void Enemy::setNode(PathVertexP newNode) {
    this->node = newNode;
    this->position.y = this->node->position.y;
    this->position.x = this->node->position.x;
}
