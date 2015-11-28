#include "Enemy.hpp"
#include "EnemyStateTracking.hpp"
#include "Game.hpp"
#include <iostream>
#include "Utils.hpp"

static constexpr float DEFAULT_ENEMY_HEALTH = 100.0f;
static constexpr float DEFAULT_ENEMY_RADIUS = 0.3f;

Enemy::Enemy() : Character(DEFAULT_ENEMY_HEALTH, Character::Team::ENEMY), position(0, 0), direction(0, 0), speed(0.0f), node(NULL) {
    circle.m_p.Set(0.0f, 0.0f);
    circle.m_radius = DEFAULT_ENEMY_RADIUS;
}

void Enemy::action(Game& state) {
    this->state->handle(state, *this);
}

void Enemy::setNode(PathVertexP newNode) {
    this->node = newNode;
    this->position.y = this->node->position.y;
    this->position.x = this->node->position.x;
}
