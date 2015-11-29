#include "TrackingEnemyFactory.hpp"

LinearEnemyTrackBehavior TrackingEnemyFactory::LinearTrackBehavior = LinearEnemyTrackBehavior();
AStarEnemyTrackBehavior TrackingEnemyFactory::AStarTrackBehavior = AStarEnemyTrackBehavior();

TrackingEnemyFactory::TrackingEnemyFactory(EnemyTrackBehavior& etb, std::shared_ptr<EnemyStateClose> onDest) :
    initState(new EnemyStateTracking(etb))
{
    onDest->setOutRange(initState);
    initState->setCloseRange(onDest);
}

std::unique_ptr<Enemy> TrackingEnemyFactory::makeEnemy() {
    std::unique_ptr<Enemy> enemy(new Enemy());
    enemy->state = initState;
    return enemy;
}
