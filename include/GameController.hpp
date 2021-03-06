#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <SFML/Graphics.hpp> // lazy includes
#include <SFML/System.hpp>

#include "Game.hpp"
#include "InputData.hpp"
#include "SquareView.hpp"
#include "SpriteView.hpp"

#include "ControlsConfig.hpp"

class GameController {
    public:
        GameController(int argc, char** argv);
        
        ~GameController();
        
        void run();
        
    private:
        static constexpr unsigned int WINDOW_WIDTH = 800;
        static constexpr unsigned int WINDOW_HEIGHT = 600;
        
        // Model
        Game game;
        
        InputData input; // TODO: move into Controls controller
        
        // Controls
        bool useController;
        ControlsConfig controlsConfig;       
        
        // Views
        sf::RenderWindow* window;
        sf::View view;
        sf::Font font;
        SquareView playerView;
        SquareView playerAim;  
        SquareView enemyView;
        SpriteView levelView;
        
        // Initialization logic
        void init();
        void initViews();
        
        // Drawing logic
        void draw();
        void drawPlayer();
        void drawAim();
        void drawEnemies();
        void drawAnimations();
        void drawLevel();
        void setViewForDrawing();
        void updateViews();
        inline float getViewRatio() const;
};
#endif
