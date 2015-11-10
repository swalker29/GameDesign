#ifndef SURVIVALSTATE_HPP
#define SURVIVALSTATE_HPP

#include <list>

#include <SFML/Graphics.hpp> // lazy includes
#include <SFML/System.hpp>

#include "AppState.hpp"
#include "ControlsConfig.hpp"
#include "Game.hpp"
#include "ImageView.hpp"
#include "InputData.hpp"
#include "SquareView.hpp"
#include "SpriteView.hpp"

class GameApp;

class SurvivalState : public AppState {
    public:
        // Default constructor
        
        // Default destructor
        
        void handle(GameApp& gameApp);
        
    private:
        static constexpr unsigned int WINDOW_WIDTH = 800;
        static constexpr unsigned int WINDOW_HEIGHT = 600;

        bool isPaused = false;
        
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
        SpriteView playerView;
        SquareView playerAim;  
        SquareView enemyView;
        SpriteView levelView;
        ImageView titleView;
        sf::Text pauseText;
        sf::Vector2f pauseTextLocation;
        
        SquareView projectileView;
        
        // Initialization logic
        void init();
        void initViews();
        void initPauseScreen();
        
        // Drawing logic for survival/campaign
        void draw();
        void drawPlayer();
        void drawAim();
        void drawEnemies();
        void drawAnimations();
        void drawLevel();
        void drawProjectiles();
        void drawPause();
        void setViewForDrawing();
        void updateViews();
        inline float getViewRatio() const;


};
#endif