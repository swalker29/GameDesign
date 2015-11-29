#include "EnemyStateClose.hpp"
void EnemyStateClose::setOutRange(std::shared_ptr<EnemyState> transition) {
    this->outRange = transition;
}
