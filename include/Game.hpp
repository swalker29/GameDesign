#ifndef GAME_HPP
#define GAME_HPP

#include <list>
#include <memory>
#include <stdint.h>
#include <Box2D/Box2D.h>

#include "Enemy.hpp"
#include "InputData.hpp"
#include "Level.hpp"
#include "Player.hpp"

class Game {
    public:
        static constexpr float TILE_SIZE = 3.0f; // We need to define our scale and set this to make sense for Box2D
        
        Player player;
        std::list<std::unique_ptr<Enemy>> enemies;
        
        std::list<sf::Vector2f> meshPoints;
        Level level;
        
        Game();

        // Default destructor
        
        bool init();
        
        //void pause();
        
        //void unpause();
        
        void update(const float timeElapsed, InputData& input);
        
        
        inline sf::Vector2i getPlayerTile() const {
            return sf::Vector2i(int(player.position.x / TILE_SIZE), int(player.position.y / TILE_SIZE)); 
        };

        inline sf::Vector2f getTilePosition(int x, int y) const {
            return sf::Vector2f(TILE_SIZE * x, TILE_SIZE * y);
        };
        
    private:
        b2World b2world;
        
        void initBox2D();
        
        void giveImpulseToBody(b2Body* b2body, sf::Vector2f desiredVelocity);
        
        void addTileElementToWorld(int x, int y);
        void removeTileElementFromWorld(int x, int y);

};
#endif
