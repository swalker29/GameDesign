#ifndef SURVIVALSTATE_HPP
#define SURVIVALSTATE_HPP

#include <list>

#include <SFML/Audio/Music.hpp>
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
        SpriteView bEnemyView;
		SpriteView oEnemyView;
		SpriteView rEnemyView;
        SpriteView levelView;
        SpriteView projectileView;
        ImageView titleView;
        sf::Text pauseText;
        sf::Vector2f relativePlayerLocation;
        SpriteView selectedWeapon;
        SpriteView bulletAmmo;
        sf::Text bulletCount;
        SpriteView shellAmmo;
        sf::Text shellCount;
        SpriteView missileAmmo;
        sf::Text missileCount;
        SpriteView healthBarFrame;
        sf::RectangleShape healthBar;
		sf::Text scoreCount;

        
        //music 
        sf::SoundBuffer lowBuffer;
        sf::SoundBuffer highBuffer;
        sf::Sound survivalMusicLow;
        sf::Sound survivalMusicHigh;
        
        // Initialization logic
        void init();
        void initViews();
        void initPauseScreen();
        void initUI();
        
        // Drawing logic for survival/campaign
        void draw();
        void drawPlayer();
        void drawAim();
        void drawEnemies();
        void drawAnimations();
        void drawLevel();
        void drawProjectiles();
        void drawPause();
        void drawUI();
        void setViewForDrawing();
        void updateViews();
        inline float getViewRatio() const;


};
#endif
