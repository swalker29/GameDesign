#ifndef ENEMYSTATEFIRING_HPP
#define ENEMYSTATEFIRING_HPP
#include "EnemyState.hpp"
#include <memory>
class EnemyStateFiring : public EnemyState {
    private:
        std::shared_ptr<EnemyState> outRange;
        float fireRate;
    public:
        EnemyStateFiring();
        EnemyStateFiring(float shotInterval);
        void setTransition(std::shared_ptr<EnemyState> outRange);
        void handle(Game& state, Enemy& enemy);
};
#endif
