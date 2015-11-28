#ifndef ENEMYSTATETRACKING_HPP
#define ENEMYSTATETRACKING_HPP
#include "EnemyState.hpp"
#include <memory>
class EnemyTrackBehavior;
class EnemyStateTracking : public EnemyState {
    private:
        std::shared_ptr<EnemyState> onDest;
        EnemyTrackBehavior* trackBehavior;
    public:
        EnemyStateTracking(EnemyTrackBehavior& trackBehavior);
        virtual void setTransition(std::shared_ptr<EnemyState> onDest);
        void handle(Game& state, Enemy& enemy);
};
#endif
