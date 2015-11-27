#include "TrackingEnemyFactory.hpp"
#include "EnemyStateTracking.hpp"

LinearEnemyTrackBehavior TrackingEnemyFactory::LinearTrackBehavior = LinearEnemyTrackBehavior();
AStarEnemyTrackBehavior TrackingEnemyFactory::AStarTrackBehavior = AStarEnemyTrackBehavior();

TrackingEnemyFactory::TrackingEnemyFactory(EnemyTrackBehavior& etb, std::shared_ptr<EnemyState> onDest) :
    initState(new EnemyStateTracking(etb))
{
    onDest->setTransition(initState);
    initState->setTransition(onDest);
}

std::unique_ptr<Enemy> TrackingEnemyFactory::makeEnemy() {
    std::unique_ptr<Enemy> enemy(new Enemy());
    enemy->state = initState;
    return enemy;
}
