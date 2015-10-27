#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/System/Vector2.hpp>
class Game;
class EnemyTrackBehavior;
class Enemy {
    private:
        EnemyTrackBehavior* trackBehavior;
        void updateNode();
        const sf::Vector2f* node;

    public:
        sf::Vector2f position;
        sf::Vector2f direction;    
        float speed, health;
        void track(const Game& state, const sf::Vector2f& target);
        void setTrackBehavior(EnemyTrackBehavior& newTrackBehavior);
        void setNode(sf::Vector2f& navMeshNode);
        Enemy();
};
#endif
