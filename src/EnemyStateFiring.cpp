#include "EnemyStateFiring.hpp"
#include "Game.hpp"
#include "Enemy.hpp"
#include <iostream>

#define DEBUGFIRING 1
EnemyStateFiring::EnemyStateFiring() {}

void EnemyStateFiring::setTransition(std::shared_ptr<EnemyState> outRange) {
    this->outRange = outRange;
}

void EnemyStateFiring::handle(const Game& state, Enemy& enemy) {

    PathVertexP targetNode = state.player.node;
    if (enemy.node && enemy.node != targetNode && this->outRange) {
        enemy.state = this->outRange;
        return;
    }

#if DEBUGFIRING
    std::cout << "BANG!" << std::endl;
#endif
}
