#ifndef ENEMYSTATEFAR_HPP
#define ENEMYSTATEFAR_HPP
#include "EnemyState.hpp"
#include <memory>
class EnemyStateFar : virtual public EnemyState {
    protected:
        std::shared_ptr<EnemyState> closeRange;
    public:
        void setCloseRange(std::shared_ptr<EnemyState> transition);
        virtual void handle(Game& state, Enemy& enemy)=0;
};
#endif
