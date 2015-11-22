#include "TrackingEnemyFactory.hpp"

LinearEnemyTrackBehavior TrackingEnemyFactory::LinearTrackBehavior = LinearEnemyTrackBehavior();
AStarEnemyTrackBehavior TrackingEnemyFactory::AStarTrackBehavior = AStarEnemyTrackBehavior();

TrackingEnemyFactory::TrackingEnemyFactory(EnemyTrackBehavior& etb) :
    etb(&etb) 
{}

std::unique_ptr<Enemy> TrackingEnemyFactory::makeEnemy() {
    std::unique_ptr<Enemy> enemy(new Enemy());
    enemy->setTrackBehavior(*(this->etb));
    return enemy;
}
