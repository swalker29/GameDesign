#ifndef ENEMYFACTORY_HPP
#define ENEMYFACTORY_HPP
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "Enemy.hpp"
class IEnemyFactory {
    protected:
        virtual std::unique_ptr<Enemy> makeEnemy()=0;
    public:
        IEnemyFactory() {}
        virtual ~IEnemyFactory() {}
        std::unique_ptr<Enemy> makeEnemyAt(sf::Vector2f start, sf::Vector2f direction, float speed);
};
#endif
