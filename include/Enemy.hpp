#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <memory>

#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>

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
        float speed;
        float health;
        float radius;
        bool stationary;
        
        b2Body* b2body;
        b2Fixture* b2fixture;
        b2CircleShape circle;
        
        TrackNode track(const Game& state, const sf::Vector2f& target);
        void setTrackBehavior(EnemyTrackBehavior& newTrackBehavior);
        void setNode(PathVertexP node);
        Enemy();
};
#endif
