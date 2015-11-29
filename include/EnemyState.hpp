#ifndef ENEMYSTATE_HPP
#define ENEMYSTATE_HPP
#include <memory>
class Game;
class Enemy;
class EnemyState {
    public:
        virtual ~EnemyState() {}
        virtual void handle(Game& state, Enemy& enemy) = 0;
        void changeState(Enemy& enemy, std::shared_ptr<EnemyState> newState);
};
typedef std::shared_ptr<EnemyState> EnemyStateP;
#endif

