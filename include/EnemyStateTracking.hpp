#ifndef ENEMYSTATETRACKING_HPP
#define ENEMYSTATETRACKING_HPP
#include "EnemyState.hpp"
class TrackNode;
class EnemyStateTracking : public EnemyState {
    public:
        EnemyStateTracking();
        void handle(const Game& state, Enemy& enemy);
};
#endif
