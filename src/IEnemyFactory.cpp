#include "IEnemyFactory.hpp"

std::unique_ptr<Enemy> IEnemyFactory::makeEnemyAt(sf::Vector2f start, sf::Vector2f direction, float speed) {
    std::unique_ptr<Enemy> enemy = this->makeEnemy();
    enemy->position = start;
    enemy->direction = direction;
    enemy->speed = speed;
    return enemy;
}

