#ifndef ENEMYSTATECLOSE_HPP
#define ENEMYSTATECLOSE_HPP
#include "EnemyState.hpp"
#include <memory>
class EnemyStateClose : virtual public EnemyState {
    protected:
        std::shared_ptr<EnemyState> outRange;
    public:
        void setOutRange(std::shared_ptr<EnemyState> transition);
        virtual void handle(Game& state, Enemy& enemy)=0;
};
#endif
