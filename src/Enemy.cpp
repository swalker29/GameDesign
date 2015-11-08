#include "Enemy.hpp"
#include "Game.hpp"
#include "EnemyTrackBehavior.hpp"
#include <iostream>

Enemy::Enemy() : position(0, 0), direction(0, 0), speed(0), node(NULL) {

}
void Enemy::track(const Game& state, const sf::Vector2f& target) {
    if (!this->trackBehavior) return;

    std::shared_ptr<PathVertex> targetNode = state.level.pathVertices[27];
    TrackNode tn = this->trackBehavior->track(state, this->position, target, this->node, targetNode);

    if (this->node == targetNode) {
        //track player within hierachy
        return;
    }
    
    this->direction = tn.direction;
    if (tn.node) this->node = tn.node;

    this->position.y -= this->speed * this->direction.y;
    this->position.x -= this->speed * this->direction.x;
}
void Enemy::setTrackBehavior(EnemyTrackBehavior& newBehavior) {
    this->trackBehavior = &newBehavior;
}

void Enemy::setNode(PathVertexP newNode) {
    this->node = newNode;
    this->position.y = this->node->position.y;
    this->position.x = this->node->position.x;
}
