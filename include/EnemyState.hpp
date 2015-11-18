#ifndef ENEMYSTATE_HPP
#define ENEMYSTATE_HPP
class Enemy;
class EnemyStateTracking;
class EnemyState {
    protected:
        static EnemyStateTracking tracking;
    public:
        virtual ~EnemyState() {}
        virtual void handle(Enemy& enemy) = 0;
};
#endif

