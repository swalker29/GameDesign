#ifndef ENEMYSTATE_HPP
#define ENEMYSTATE_HPP
class Game;
class Enemy;
class EnemyState {
    public:
        virtual ~EnemyState() {}
        virtual void handle(Game& state, Enemy& enemy) = 0;
};
#endif

