#ifndef ENEMYSTATE_HPP
#define ENEMYSTATE_HPP
#include <memory>
class Game;
class Enemy;
class EnemyState {
    public:
        virtual ~EnemyState() {}
        virtual void setTransition(std::shared_ptr<EnemyState> nextState) {}
        virtual void handle(const Game& state, Enemy& enemy) = 0;
};
#endif

