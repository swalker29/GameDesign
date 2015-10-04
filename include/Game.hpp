#ifndef GAME_HPP
#define GAME_HPP

#include <list>
#include <memory>
#include <stdint.h>

#include "Enemy.hpp"
#include "InputData.hpp"
#include "Level.hpp"
#include "Player.hpp"

class Game {
    public:
        static constexpr float MAX_X = 4.0f;
        static constexpr float MIN_X = 0.0f;
        static constexpr float MAX_Y = 3.0f;
        static constexpr float MIN_Y = 0.0f;
        static constexpr float TILE_SIZE = 3.0f; // We need to define our scale and set this to make sense for Box2D
        
        Player player;
        std::list<std::unique_ptr<Enemy>> enemies;
        
        Level level;
        
        Game();
        
        //void pause();
        
        //void unpause();
        
        void update(const float timeElapsed, InputData& input);
        
        inline sf::Vector2i getPlayerTile() {
            return sf::Vector2i(int(player.position.x / TILE_SIZE), int(player.position.y / TILE_SIZE)); 
        };

        inline sf::Vector2f getTilePosition(int x, int y) {
            return sf::Vector2f(TILE_SIZE * x, TILE_SIZE * y);
        };
        
    private:
};
#endif
