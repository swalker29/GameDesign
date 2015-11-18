#ifndef ENEMYSTATEMELEE_HPP
#define ENEMYSTATEMELEE_HPP
#include "EnemyState.hpp"
class EnemyStateMelee : EnemyState {
    public:
        EnemyStateMelee();
        void handle(Enemy& enemy);
};
#endif
