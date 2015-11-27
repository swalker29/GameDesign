#ifndef ENEMYSTATEMELEE_HPP
#define ENEMYSTATEMELEE_HPP
#include "EnemyState.hpp"
class EnemyStateMelee : EnemyState {
    public:
        EnemyStateMelee();
        void handle(const Game& state, Enemy& enemy);
};
#endif
