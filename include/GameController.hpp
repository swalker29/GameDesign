#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <SFML/Graphics.hpp> // lazy includes
#include <SFML/System.hpp>

#include "Game.hpp"
#include "InputData.hpp"
#include "SquareView.hpp"

class GameController {
    public:
        GameController(int argc, char** argv);
        
        ~GameController();
        
        void run();
        
    private:
        // Model
        Game game;
        
        InputData input;        
        
        // Views
        sf::RenderWindow* window;
        sf::Font font;
        SquareView playerView;
        SquareView playerAim;  
        SquareView enemyView;
        
        // Controls
        bool useController;
        
        void draw();
        void drawPlayer();
        void drawAim();
        void drawEnemies();
        void drawLevel();
        
        // Input methods
        void getInput();
        void getControllerInput();
        void getMouseAndKeyboardInput();
        
        // View methods
        void initViews();
        void updateViews();
        float getViewRatio();
};
#endif
