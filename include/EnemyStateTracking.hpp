#ifndef ENEMYSTATETRACKING_HPP
#define ENEMYSTATETRACKING_HPP
#include "EnemyStateFar.hpp"
#include "EnemyStateClose.hpp"
class EnemyTrackBehavior;
class EnemyStateTracking : public EnemyStateFar, public EnemyStateClose {
    private:
        EnemyTrackBehavior* trackBehavior;
    public:
        EnemyStateTracking(EnemyTrackBehavior& trackBehavior);
        void handle(Game& state, Enemy& enemy);
};
#endif
