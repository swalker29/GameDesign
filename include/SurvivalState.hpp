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
        SurvivalState();
        //SurvivalState(const SurvivalState&) = delete;
       // SurvivalState& operator = (const SurvivalState&) = delete;
        
        ~SurvivalState();
        
        void handle(GameApp& gameApp);
        
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
        ImageView titleView;
        
        SquareView projectileView;
        
        // Initialization logic
        void init();
        void initViews();
        
        // Drawing logic for survival/campaign
        void draw();
        void drawPlayer();
        void drawAim();
        void drawEnemies();
        void drawAnimations();
        void drawLevel();
        void drawProjectiles();
        void setViewForDrawing();
        void updateViews();
        inline float getViewRatio() const;

        // Drawing logic for main menu
        void drawMainMenu();
        void drawTitle();
        void drawButtons();
        void drawMenuAssets();


};
#endif
