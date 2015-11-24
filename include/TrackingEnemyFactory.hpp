#ifndef TRACKINGENEMYFACTORY_HPP
#define TRACKINGENEMYFACTORY_HPP
#include "IEnemyFactory.hpp"
#include "LinearEnemyTrackBehavior.hpp"
#include "AStarEnemyTrackBehavior.hpp"

class TrackingEnemyFactory : public IEnemyFactory {
    private:
        EnemyTrackBehavior* etb;
        EnemyTrackBehavior* fallback;
    protected:
        virtual std::unique_ptr<Enemy> makeEnemy();
    public:
        static LinearEnemyTrackBehavior LinearTrackBehavior;
        static AStarEnemyTrackBehavior AStarTrackBehavior;
        TrackingEnemyFactory(EnemyTrackBehavior& etb, EnemyTrackBehavior& fallback);
};
#endif
