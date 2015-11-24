#include "Enemy.hpp"
#include "EnemyStateMelee.hpp"
#include "EnemyStateTracking.hpp"
#include "Game.hpp"
#include <iostream>
#include "Utils.hpp"

static constexpr float DEFAULT_ENEMY_HEALTH = 100.0f;
static constexpr float DEFAULT_ENEMY_RADIUS = 0.3f;

Enemy::Enemy() : Character(DEFAULT_ENEMY_HEALTH, Character::Team::ENEMY), position(0, 0), direction(0, 0), speed(0.0f), node(NULL) , stationary(false) {
    circle.m_p.Set(0.0f, 0.0f);
    circle.m_radius = DEFAULT_ENEMY_RADIUS;
}
void Enemy::track(const Game& state, PathVertexP targetNode, const sf::Vector2f& target) {
    TrackNode tn;
    if (!this->trackBehavior || this->stationary) {
        tn.node = this->node;
        tn.direction = sf::Vector2f(0,0);
    } else if (this->node && this->node == targetNode) { 
        sf::Vector2f direction = target - this->position;
        normalizeVector2f(direction);
        tn.direction = direction;

        tn = this->fallbackBehavior->track(state, this->position, target, this->node, targetNode);
    } else {
        tn = this->trackBehavior->track(state, this->position, target, this->node, targetNode);
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

void Enemy::setFallbackBehavior(EnemyTrackBehavior& newBehavior) {
    this->fallbackBehavior = &newBehavior;
}

void Enemy::setNode(PathVertexP newNode) {
    this->node = newNode;
    this->position.y = this->node->position.y;
    this->position.x = this->node->position.x;
}
