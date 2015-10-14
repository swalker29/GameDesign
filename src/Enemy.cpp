#include "Enemy.hpp"
#include "EnemyTrackBehavior.hpp"

Enemy::Enemy() : position(0, 0), direction(0, 0), speed(0) {

}
void Enemy::track(sf::Vector2f playerPos) {
    if (!this->trackBehavior) return;

    this->direction = this->trackBehavior->track(this->position, playerPos);
    this->position.y -= this->speed * this->direction.y;
    this->position.x -= this->speed * this->direction.x;
}
void Enemy::setTrackBehavior(EnemyTrackBehavior& newBehavior) {
    this->trackBehavior = &newBehavior;
}
