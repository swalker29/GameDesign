#include "Game.hpp"

#include "LinearEnemyTrackBehavior.hpp"
#include <stdio.h>

// Default constructor

// Default destructor

bool Game::init() {
    
    const int nEnemies = 10;
    sf::Vector2f start(0.5, 0);
    for (int i=0; i < nEnemies; i++) {
        std::unique_ptr<Enemy> enemy(new Enemy());
        enemy->position = start;
        enemy->setTrackBehavior(enemy->linearTrackBehavior);
        start.x += 0.15;
        this->enemies.push_back(std::move(enemy));
    }
    
    return true;
}

void Game::update(const float timeElapsed, InputData& input) {
    // get actions from input
    player.position += 0.03f * input.movement;
    
    if (input.aim.x != 0 || input.aim.y != 0) {
        player.direction = input.aim;
    }
    
    // all the real game logic starts here
    for (auto& enemy : this->enemies) {
        enemy->track(player.position);
    }
}
