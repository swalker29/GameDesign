#include "IEnemyFactory.hpp"

std::unique_ptr<Enemy> IEnemyFactory::makeEnemyAt(PathVertexP node, sf::Vector2f& direction, float speed) {
    std::unique_ptr<Enemy> enemy = this->makeEnemy();
    enemy->node = node;
    enemy->position = node->position;
    enemy->direction = direction;
    enemy->speed = speed;
    
    return enemy;
}

