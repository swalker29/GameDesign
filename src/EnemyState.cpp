#include "EnemyState.hpp"
#include "Enemy.hpp"

void EnemyState::changeState(Enemy& enemy, EnemyStateP newState) {
    enemy.timer.restart();
    enemy.speed = enemy.origSpeed;

    enemy.state = newState;
}
