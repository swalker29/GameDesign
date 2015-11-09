#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <SFML/System/Vector2.hpp>
#include <memory>
#include "EnemyTrackBehavior.hpp"
#include "PathVertex.hpp"
class Game;
class EnemyTrackBehavior;
class Enemy {
    private:
        EnemyTrackBehavior* trackBehavior;
        void updateNode();

    public:
        PathVertexP node;
        sf::Vector2f position;
        sf::Vector2f direction;    
        float speed, health;
        bool stationary;
        TrackNode track(const Game& state, const sf::Vector2f& target);
        void setTrackBehavior(EnemyTrackBehavior& newTrackBehavior);
        void setNode(PathVertexP node);
        Enemy();
};
#endif
