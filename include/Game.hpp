#ifndef GAME_HPP
#define GAME_HPP

#include <stdint.h>

#include "InputData.hpp"
#include "Player.hpp"

class Game {
    public:
        static constexpr float MAX_X = 4.0f;
        static constexpr float MIN_X = 0.0f;
        static constexpr float MAX_Y = 3.0f;
        static constexpr float MIN_Y = 0.0f;
        
        Player player;
        
        Game();
        
        //void pause();
        
        //void unpause();
        
        void update(const float timeElapsed, InputData& input);
        
    private:

};
#endif
