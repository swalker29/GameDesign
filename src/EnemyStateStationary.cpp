#include "EnemyStateStationary.hpp"
#include "EnemyTrackBehavior.hpp"
#include "Enemy.hpp"

void EnemyStateStationary::handle(Game& state, Enemy& enemy) {
    TrackNode tn;
    tn.node = enemy.node;
    tn.direction = sf::Vector2f(0,0);

    enemy.tracking = tn;
}
