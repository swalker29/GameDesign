#ifndef ENEMYSTATEFIRING_HPP
#define ENEMYSTATEFIRING_HPP
#include "EnemyStateClose.hpp"
class EnemyStateFiring : public EnemyStateClose {
    private:
        float fireRate;
    public:
        EnemyStateFiring();
        EnemyStateFiring(float shotInterval);
        void handle(Game& state, Enemy& enemy);
};
#endif
