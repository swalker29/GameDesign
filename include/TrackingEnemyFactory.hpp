#ifndef TRACKINGENEMYFACTORY_HPP
#define TRACKINGENEMYFACTORY_HPP
#include "IEnemyFactory.hpp"
#include "LinearEnemyTrackBehavior.hpp"

class TrackingEnemyFactory : public IEnemyFactory {
    private:
        EnemyTrackBehavior* etb;
    protected:
        virtual std::unique_ptr<Enemy> makeEnemy();
    public:
        static LinearEnemyTrackBehavior linearTrackBehavior;
        TrackingEnemyFactory(EnemyTrackBehavior& etb);
};
#endif
