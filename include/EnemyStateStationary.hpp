#ifndef ENEMYSTATESTATIONARY_HPP
#define ENEMYSTATESTATIONARY_HPP
#include "EnemyState.hpp"
class EnemyStateStationary : public EnemyState {
    public:
        void handle(const Game& state, Enemy& enemy);
};
#endif
