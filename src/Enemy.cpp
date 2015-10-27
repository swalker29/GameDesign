#include "Enemy.hpp"
#include "Game.hpp"
#include "EnemyTrackBehavior.hpp"

Enemy::Enemy() : position(0, 0), direction(0, 0), speed(0), node(NULL) {

}
void Enemy::track(const Game& state, const sf::Vector2f& target) {
    if (!this->trackBehavior) return;

    TrackNode tn = this->trackBehavior->track(state, *node, this->position, target);

    this->direction = tn.direction;
    if (tn.node) this->node = tn.node;

    this->position.y -= this->speed * this->direction.y;
    this->position.x -= this->speed * this->direction.x;
}
void Enemy::setTrackBehavior(EnemyTrackBehavior& newBehavior) {
    this->trackBehavior = &newBehavior;
}

void Enemy::setNode(sf::Vector2f& navMeshNode) {
    this->node = &navMeshNode;
    this->position.y = navMeshNode.y;
    this->position.x = navMeshNode.x;
}
