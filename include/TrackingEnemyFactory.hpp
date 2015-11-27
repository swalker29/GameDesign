#ifndef TRACKINGENEMYFACTORY_HPP
#define TRACKINGENEMYFACTORY_HPP
#include "IEnemyFactory.hpp"
#include "LinearEnemyTrackBehavior.hpp"
#include "AStarEnemyTrackBehavior.hpp"
#include "EnemyStateTracking.hpp"
#include <memory>

class TrackingEnemyFactory : public IEnemyFactory {
    private:
        std::shared_ptr<EnemyStateTracking> initState;
    protected:
        virtual std::unique_ptr<Enemy> makeEnemy();
    public:
        static LinearEnemyTrackBehavior LinearTrackBehavior;
        static AStarEnemyTrackBehavior AStarTrackBehavior;
        TrackingEnemyFactory(EnemyTrackBehavior& etb, std::shared_ptr<EnemyState> onDest);
};
#endif
