#include "Enemy.hpp"
#include "EnemyTrackBehavior.hpp"
#include "LinearEnemyTrackBehavior.hpp"

LinearEnemyTrackBehavior Enemy::linearTrackBehavior = LinearEnemyTrackBehavior();

Enemy::Enemy() : position(0.0f, 0.0f), direction(1.0f, 0.0f), speed(0.01) {

}
void Enemy::track(sf::Vector2f playerPos) {
    this->direction = this->trackBehavior->track(this->position, playerPos);
    this->position.y -= this->speed * this->direction.y;
    this->position.x -= this->speed * this->direction.x;
}
void Enemy::setTrackBehavior(EnemyTrackBehavior& newBehavior) {
    this->trackBehavior = &newBehavior;
}
