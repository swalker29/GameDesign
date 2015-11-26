#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <memory>

#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>

#include "Character.hpp"
#include "EnemyTrackBehavior.hpp"
#include "PathVertex.hpp"

class Game;
class EnemyTrackBehavior;
class EnemyState;

class Enemy : public Character {
    private:
        void updateNode();

    public:
        EnemyTrackBehavior* trackBehavior;
        EnemyTrackBehavior* fallbackBehavior;
        EnemyState* state;
        PathVertexP node;
        sf::Vector2f position;
        sf::Vector2f direction;    
        float speed;
        bool stationary;
        TrackNode tracking;
        
        b2Body* b2body;
        b2Fixture* b2fixture;
        b2CircleShape circle;

        void action(const Game& state);
        
        void setTrackBehavior(EnemyTrackBehavior& newTrackBehavior);
        void setFallbackBehavior(EnemyTrackBehavior& newTrackBehavior);
        void setNode(PathVertexP node);
        Enemy();
};
#endif
