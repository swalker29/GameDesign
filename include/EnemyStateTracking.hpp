#ifndef ENEMYSTATETRACKING_HPP
#define ENEMYSTATETRACKING_HPP
#include "EnemyState.hpp"
class EnemyStateTracking : public EnemyState {
    public:
        EnemyStateTracking();
        void handle(Enemy& enemy);
};
#endif
