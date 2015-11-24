#include "TrackingEnemyFactory.hpp"

LinearEnemyTrackBehavior TrackingEnemyFactory::LinearTrackBehavior = LinearEnemyTrackBehavior();
AStarEnemyTrackBehavior TrackingEnemyFactory::AStarTrackBehavior = AStarEnemyTrackBehavior();

TrackingEnemyFactory::TrackingEnemyFactory(EnemyTrackBehavior& etb, EnemyTrackBehavior& fallback) :
    etb(&etb), fallback(&fallback)
{}

std::unique_ptr<Enemy> TrackingEnemyFactory::makeEnemy() {
    std::unique_ptr<Enemy> enemy(new Enemy());
    enemy->setTrackBehavior(*(this->etb));
    enemy->setFallbackBehavior(*(this->fallback));
    return enemy;
}
