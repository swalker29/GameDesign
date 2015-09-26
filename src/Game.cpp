#include "Game.hpp"

#include <stdio.h>

Game::Game() {

}

// default destructor

void Game::update(const float timeElapsed, InputData& input) {
    // get actions from input
    player.position += 0.03f * input.movement;
    
    if (input.aim.x != 0 || input.aim.y != 0) {
        player.direction = input.aim;
    }
    
    // all the real game logic starts here
}

