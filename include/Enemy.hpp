#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <memory>

#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
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
        sf::Clock timer;
        std::shared_ptr<EnemyState> state;
        PathVertexP node;
        sf::Vector2f position;
        sf::Vector2f direction;    
        float speed;
        float origSpeed;
        TrackNode tracking;
        
        b2Body* b2body;
        b2Fixture* b2fixture;
        b2CircleShape circle;

        void action(Game& state);
        
        void setNode(PathVertexP node);
        Enemy();
};
#endif
