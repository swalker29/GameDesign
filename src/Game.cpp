#include "Game.hpp"
#include <string>
#include <cstdio>
#include "TrackingEnemyFactory.hpp"

static const std::string LEVEL_FILE = "assets/map.level";

// Default constructor

// Default destructor

bool Game::init() {
    
    if (!level.init(LEVEL_FILE, &this->meshPoints)) {
        return false;
    }
    
    const int nEnemies = 10;
    sf::Vector2f start(0.5, 0);
    sf::Vector2f direction(0,1);
    float speed = 0.01;

    TrackingEnemyFactory linearEF(TrackingEnemyFactory::linearTrackBehavior);

    for (int i=0; i < nEnemies; i++) {
        std::unique_ptr<Enemy> enemy = linearEF.makeEnemyAt(start, direction, speed);
        start.x += 0.15;
        this->enemies.push_back(std::move(enemy));
    }
    
    return true;
}

void Game::update(const float timeElapsed, InputData& input) {
    // get actions from input
    player.position += 0.13f * input.movement;
    
    if (input.aim.x != 0 || input.aim.y != 0) {
        player.direction = input.aim;
    }
    
    // all the real game logic starts here
    for (auto& enemy : this->enemies) {
        sf::Vector2i playerTile = this->getPlayerTile();
        sf::Vector2f tilePos = this->getTilePosition(playerTile.x, playerTile.y);
        sf::Vector2f tileCenter = sf::Vector2f(tilePos.x + TILE_SIZE/2, tilePos.y + TILE_SIZE/2);
        enemy->track(tileCenter);
        //enemy->track(player.position);
    }
}
