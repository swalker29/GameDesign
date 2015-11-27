#ifndef ENEMYSTATEFIRING_HPP
#define ENEMYSTATEFIRING_HPP
#include "EnemyState.hpp"
#include <memory>
class EnemyStateFiring : public EnemyState {
    private:
        std::shared_ptr<EnemyState> outRange;
    public:
        EnemyStateFiring();
        void setTransition(std::shared_ptr<EnemyState> outRange);
        void handle(const Game& state, Enemy& enemy);
};
#endif
