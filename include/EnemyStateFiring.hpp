#ifndef ENEMYSTATEFIRING_HPP
#define ENEMYSTATEFIRING_HPP
#include "EnemyState.hpp"
class EnemyStateFiring : public EnemyState {
    public:
        EnemyStateFiring();
        void handle(const Game& state, Enemy& enemy);
};
#endif
