#ifndef ENEMYSTATEPOUNCING_HPP
#define ENEMYSTATEPOUNCING_HPP
#include "EnemyStateClose.hpp"
class EnemyStatePouncing : public EnemyStateClose {
    private:
        float primeSpeed;
        float pounceSpeed;
    public:
        EnemyStatePouncing();
        EnemyStatePouncing(float primeSpeed, float pounceSpeed);
        void handle(Game& state, Enemy& enemy);
};
#endif
