#include "IEnemyFactory.hpp"

std::unique_ptr<Enemy> IEnemyFactory::makeEnemyAt(PathVertexP node, sf::Vector2f& direction, float speed) {
    std::unique_ptr<Enemy> enemy = this->makeEnemy();
    enemy->node = node;
    enemy->position = node->position;
    enemy->direction = direction;
    enemy->speed = speed;
    
    enemy->circle.m_p.Set(0.0f, 0.0f);
    enemy->circle.m_radius = enemy->radius;
    
    return enemy;
}

