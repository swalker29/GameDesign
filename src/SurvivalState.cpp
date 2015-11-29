#include "SurvivalState.hpp"

#include "Utils.hpp"

#define FPS 60
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

static const std::string FONT_FILENAME = "assets/DroidSans.ttf";
static const std::string LEVEL_TILE_SHEET_FILENAME = "assets/tileset.png";
static const std::string PLAYER_TILE_SHEET_FILENAME = "assets/playerSpritesheet.png";
static const std::string MUSIC_HIGH_FILENAME = "assets/survivalHighMusic.wav";
static const std::string MUSIC_LOW_FILENAME = "assets/survivalLowMusic.wav";
static constexpr char* CONTROL_CONFIG_FILENAME = (char*)"assets/config.txt";

static constexpr int PLAYER_SPRITE_WIDTH = 128;

// Default constructor

// Default destructor

void SurvivalState::handle(GameApp& gameApp) {
    window = gameApp.getWindow();

   
    sf::Time elapsed;
    sf::Clock clock;

    init();

    // start main loop
    while(window->isOpen()) {
        // process events
        sf::Event event;
        
        while(window->pollEvent(event)) {
            // Exit
            if(event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::LostFocus) {
                // loop until we get the GainedFocus event. Wait for the event so the thread can sleep and not use CPU.
                while (event.type != sf::Event::GainedFocus) {
                    window->waitEvent(event);
                    
                    // draw in case the screen was resized or another window was placed on top before
                    draw();
                }
                // restart the clock so we don't have an incredibly long elapsed time
                clock.restart();
            }
            //handle pausing event
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    if(isPaused == false) {
                        isPaused = true;
                    } else { isPaused = false; }
                }
            }
        }
        
        // Leave this here instead of in getInput() because if the controller gets disconnected we should pause.
        sf::Joystick::update();
        useController = sf::Joystick::isConnected(0); //call this inside ControlsConfig

        controlsConfig.getInput(useController, window);
        
        elapsed = clock.restart();
        
        //only update gamelogic and draw the game if the game isn't paused
        if(isPaused == false) {
            game.update(elapsed.asSeconds(), controlsConfig.input);
            draw();
			//Changes to volume for dynamic music.
			survivalMusicHigh.setVolume(100+game.player.health);
			survivalMusicLow.setVolume(100-100+game.player.health);
        } else {
            drawPause();
        }
		
    }

    return;

} 

void SurvivalState::init() {
    if (!game.init()) {
        fprintf(stderr, "Error initializing game. Program exiting.\n");
        fflush(stdout);
        std::exit(-1);
    }
    
    initViews();
    
    
    // control configuration initialization
    if (!controlsConfig.loadControlsConfig(CONTROL_CONFIG_FILENAME)) {
        fprintf(stderr, "Error initializing control configuration. Program exiting.\n");
        fflush(stdout);
        std::exit(-1);
    }
    
    // no resize
    view.setSize(SurvivalState::WINDOW_WIDTH, SurvivalState::WINDOW_HEIGHT);
    
    window->setFramerateLimit(60);
	
	if (!lowBuffer.loadFromFile(MUSIC_LOW_FILENAME))
		fprintf(stderr, "Error: Unable to load survival music (low).\n");
	if (!highBuffer.loadFromFile(MUSIC_HIGH_FILENAME))
		fprintf(stderr, "Error: Unable to load survival music (high).\n");
	survivalMusicLow.setBuffer(lowBuffer);
	survivalMusicHigh.setBuffer(highBuffer);
	survivalMusicLow.play();
	survivalMusicHigh.play();
	survivalMusicLow.setVolume(0);
	survivalMusicLow.setLoop(true);
	survivalMusicHigh.setLoop(true);
}

void SurvivalState::initViews() {
    
    if (!font.loadFromFile(FONT_FILENAME)) {
        fprintf(stderr, "Error: Unable to load font. Program exiting\n");
        std::exit(-1);
    }
    if (!levelView.init(LEVEL_TILE_SHEET_FILENAME, game.level.tileLength, game.level.tileLength)) {
        fprintf(stderr, "Error: Unable to load level tile sheet. Program exiting\n");
        std::exit(-1);
    }
    if (!playerView.init(PLAYER_TILE_SHEET_FILENAME, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_WIDTH)) {
        fprintf(stderr, "Error: Unable to load player sprite sheet. Program exiting\n");
        std::exit(-1);
    }

    initPauseScreen();

    enemyView.length = 10.0f;
    playerAim.length = 5.0f;    
    projectileView.length = 2.0f; 
}

void SurvivalState::initPauseScreen() {
    
    pauseText.setFont(font);
    pauseText.setCharacterSize(50);
    pauseText.setColor(sf::Color::Blue);
    pauseText.setString("PAUSED: \n press Esc to resume");
    
}

//handles drawing the game
void SurvivalState::draw() {
    window->clear(sf::Color::Black);

    setViewForDrawing();

    drawLevel();
    drawPlayer();
    drawAim();
    drawEnemies();
    drawProjectiles();

    window->display();
}

void SurvivalState::drawPlayer() {
    float ratio = getViewRatio();
    
    playerView.position = ratio * game.player.position - sf::Vector2f(PLAYER_SPRITE_WIDTH / 2.0f, PLAYER_SPRITE_WIDTH / 2.0f);
    
    // Draw/Animate legs here
    // TODO: do animation the legs should be drawn walking in the direction the player is moving
    // playerView.updateSprite(current leg stuff)
    
    // Now draw the top
    float rotation = std::atan2(game.player.direction.x, game.player.direction.y);
    rotation = -180.0f * rotation / M_PI + 180.0f;
    
    playerView.rotation = rotation;
    playerView.updateSprite(10 + game.weapons[game.player.activeWeapon].playerSpriteIndex);
    playerView.draw(window);
}

void SurvivalState::drawAim() {
    float ratio = getViewRatio();
    playerAim.position = ratio * (game.player.position + 2.0f * game.player.direction);  
    playerAim.draw(window);
}

void SurvivalState::drawEnemies() {
    float ratio = getViewRatio();
    for (auto& enemy : game.enemies) {
        enemyView.position = ratio * enemy->position;
        enemyView.draw(window);
    }
}

void SurvivalState::drawLevel() {
    sf::Vector2i playerTile = game.getPlayerTile();
    float viewRatio = getViewRatio();
    
    // TODO: get a better number than 5 for what to draw around the player based on tile size and game window
    int xLow = std::max(0, playerTile.x - 5) ;
    int xHigh = std::min(game.level.width - 1, playerTile.x + 5);
    int yLow = std::max(0, playerTile.y - 5);
    int yHigh = std::min(game.level.height - 1, playerTile.y + 5);
    
    for (int x = xLow; x <= xHigh; x++) {
        for (int y = yLow; y <= yHigh; y++) {
            levelView.updateSprite(game.level.tileVector[game.level.tiles[x][y].resource].tileMapPosition);
            levelView.position = sf::Vector2f(x * game.level.tileLength, y * game.level.tileLength);
            levelView.rotation = 90 * game.level.tiles[x][y].rotation;
            levelView.draw(window);
        }
    }    
}

void SurvivalState::drawProjectiles() {
    float ratio = getViewRatio();
    
    for (auto iter = game.projectileInstances.begin(); iter != game.projectileInstances.end(); iter++) {        
        projectileView.position = ratio * (*iter)->position - sf::Vector2f(1.0f, 1.0f);
        projectileView.draw(window);
    }   
}

void SurvivalState::drawPause() {
    float ratio = getViewRatio();
    pauseTextLocation = ratio * (game.player.position + 2.0f * game.player.direction);
    pauseText.setPosition(pauseTextLocation.x - 300, pauseTextLocation.y - 200);
    window->draw(pauseText);
    window->display();
}

void SurvivalState::setViewForDrawing() {
    float viewRatio = getViewRatio();
    view.setCenter(sf::Vector2f(std::round(game.player.position.x * getViewRatio()), std::round(game.player.position.y * getViewRatio())));
    window->setView(view);
}

inline float SurvivalState::getViewRatio() const {    
    return game.level.tileLength / Game::TILE_SIZE;
}
