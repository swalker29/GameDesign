#include "EnemyStateFar.hpp"

void EnemyStateFar::setCloseRange(std::shared_ptr<EnemyState> transition) {
    this->closeRange = transition;
}
