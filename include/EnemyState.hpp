#ifndef ENEMYSTATE_HPP
#define ENEMYSTATE_HPP
class Game;
class Enemy;
class EnemyStateTracking;
class EnemyStateFiring;
class EnemyState {
    public:
        static EnemyStateFiring firing;
        static EnemyStateTracking tracking;
        virtual ~EnemyState() {}
        virtual void handle(const Game& state, Enemy& enemy) = 0;
};
#endif

