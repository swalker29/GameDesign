#include "SurvivalState.hpp"

#include "Utils.hpp"

#define FPS 60
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

static const std::string FONT_FILENAME = "assets/DroidSans.ttf";
static const std::string LEVEL_TILE_SHEET_FILENAME = "assets/tileset.png";
static const std::string PLAYER_TILE_SHEET_FILENAME = "assets/playerSpritesheet.png";
static const std::string HEALTH_FRAME_FILENAME = "assets/healthFrame.png";
static const std::string WEAPON_SELECT_SHEET_FILENAME = "assets/weaponSelections.png";
static const std::string MUSIC_HIGH_FILENAME = "assets/survivalHighMusic.wav";
static const std::string MUSIC_LOW_FILENAME = "assets/survivalLowMusic.wav";
static const std::string PROJECTILES_SHEET_FILENAME = "assets/projectiles.png";
static const std::string B_SPIDER_SHEET_FILENAME = "assets/spiderBlueSpritesheet.png";
static const std::string O_SPIDER_SHEET_FILENAME = "assets/spiderOrangeSpritesheet.png";
static const std::string R_SPIDER_SHEET_FILENAME = "assets/spiderRedSpritesheet.png";
static constexpr char* CONTROL_CONFIG_FILENAME = (char*)"assets/config.txt";

static constexpr int B_SPIDER_WIDTH = 32;
static constexpr int O_SPIDER_WIDTH = 64;
static constexpr int R_SPIDER_WIDTH = 128;
static constexpr int PLAYER_SPRITE_WIDTH = 128;
static constexpr int PROJECTILE_SPRITE_WIDTH = 32;

static constexpr int NUM_ENEMY_FRAMES = 8;
static constexpr float ENEMY_ANIMATION_DISTANCE = 0.02f;
static constexpr int NUM_PLAYER_FRAMES = 10;
static constexpr float PLAYER_ANIMATION_DISTANCE = 0.07;

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
			survivalMusicHigh.setVolume(game.player.health);
			survivalMusicLow.setVolume(100-game.player.health);
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
    if (!bEnemyView.init(B_SPIDER_SHEET_FILENAME, B_SPIDER_WIDTH, B_SPIDER_WIDTH)) {
        fprintf(stderr, "Error: Unable to load blue spider sprite sheet. Program exiting\n");
        std::exit(-1);
    }
	if (!oEnemyView.init(O_SPIDER_SHEET_FILENAME, O_SPIDER_WIDTH, O_SPIDER_WIDTH)) {
        fprintf(stderr, "Error: Unable to load orange spider sprite sheet. Program exiting\n");
        std::exit(-1);
    }
	if (!rEnemyView.init(R_SPIDER_SHEET_FILENAME, R_SPIDER_WIDTH, R_SPIDER_WIDTH)) {
        fprintf(stderr, "Error: Unable to load red spider sprite sheet. Program exiting\n");
        std::exit(-1);
    }
    if (!projectileView.init(PROJECTILES_SHEET_FILENAME, PROJECTILE_SPRITE_WIDTH, PROJECTILE_SPRITE_WIDTH)) {
        fprintf(stderr, "Error: Unable to load projectile sprite sheet. Program exiting\n");
        std::exit(-1);
    }

    initPauseScreen();
    initUI();

    //enemyView.length = 10.0f;
    playerAim.length = 5.0f;    
}

void SurvivalState::initPauseScreen() {
    
    pauseText.setFont(font);
    pauseText.setCharacterSize(50);
    pauseText.setColor(sf::Color::Blue);
    pauseText.setString("PAUSED: \n press Esc to resume");
    
}

void SurvivalState::initUI(){

    if (!healthBarFrame.init(HEALTH_FRAME_FILENAME, 300, 50)) {
        fprintf(stderr, "Error: Unable to load health bar frame. Program exiting\n");
        std::exit(-1);
    }
    if (!selectedWeapon.init(WEAPON_SELECT_SHEET_FILENAME, 100, 100)) {
        fprintf(stderr, "Error: Unable to load weapon selection tilesheet. Program exiting\n");
        std::exit(-1);
    }

    scoreCount.setFont(font);
    scoreCount.setCharacterSize(50);
    scoreCount.setColor(sf::Color::Cyan);
    scoreCount.setStyle(sf::Text::Bold);
    scoreCount.setString("0");

    ammoCount.setFont(font);
    ammoCount.setCharacterSize(25);
    ammoCount.setColor(sf::Color::Black);
    ammoCount.setStyle(sf::Text::Bold);
    ammoCount.setString("0");
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
    drawUI();

    window->display();
}

void SurvivalState::drawPlayer() {
    float ratio = getViewRatio();
    
    playerView.position = ratio * game.player.position - sf::Vector2f(PLAYER_SPRITE_WIDTH / 2.0f, PLAYER_SPRITE_WIDTH / 2.0f);
    
    // Draw/Animate legs here
    float legRotation = std::atan2(game.player.movementDirection.y, game.player.movementDirection.x);
    legRotation = 180.0f * legRotation / M_PI + 90.0f;
    int currentLegFrame = (int) (game.player.distanceTraveled / PLAYER_ANIMATION_DISTANCE) % NUM_PLAYER_FRAMES;
    
    playerView.updateSprite(currentLegFrame);
    playerView.rotation = legRotation;
    playerView.draw(window);
    
    // Now draw the top
    float rotation = std::atan2(game.player.direction.y, game.player.direction.x);
    rotation = 180.0f * rotation / M_PI + 90.0f;
    
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
        SpriteView* enemyView = nullptr;
        int spiderWidth = 0;
        
        switch (enemy->attackType) {
            case 3:
                enemyView = &bEnemyView;
                spiderWidth = B_SPIDER_WIDTH;
            break;
            case 1:
                enemyView = &oEnemyView;
                spiderWidth = O_SPIDER_WIDTH;
            break;
            case 2:
                enemyView = &rEnemyView;
                spiderWidth = R_SPIDER_WIDTH;
            break;
            default:
                enemyView = &oEnemyView;
                spiderWidth = O_SPIDER_WIDTH;
            break;
        }
        
        enemyView->position = ratio * enemy->position - sf::Vector2f(spiderWidth / 2.0f, spiderWidth / 2.0f);
        
		float rotation = std::atan2(enemy->direction.y, enemy->direction.x);
		rotation = 180.0f * rotation / M_PI + 90.0f;
    
        int currentFrame = (int) (enemy->distanceTraveled / ENEMY_ANIMATION_DISTANCE) % NUM_ENEMY_FRAMES;
    
        enemyView->updateSprite(currentFrame);
		enemyView->rotation = rotation;
		enemyView->draw(window);
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
    
    for (auto& projectile : game.projectileInstances) {        
        projectileView.position = ratio * projectile->position - sf::Vector2f(PROJECTILE_SPRITE_WIDTH / 2.0f, PROJECTILE_SPRITE_WIDTH / 2.0f);
        
        float rotation = std::atan2(projectile->direction.y, projectile->direction.x);
        rotation = 180.0f * rotation / M_PI + 90.0f;
    
        projectileView.rotation = rotation;
        
        projectileView.updateSprite(game.projectiles[projectile->projectileIndex].projectileSpriteIndex);
        projectileView.draw(window);
    }   
}

void SurvivalState::drawPause() {
    float ratio = getViewRatio();
    relativePlayerLocation = ratio * (game.player.position);
    pauseText.setPosition(relativePlayerLocation.x - 300, relativePlayerLocation.y - 200);
    window->draw(pauseText);
    window->display();
}

void SurvivalState::drawUI() {
    float ratio = getViewRatio();
    relativePlayerLocation = ratio * (game.player.position);

    /*
    * drawing the healthbar
    */
    healthBarFrame.position = sf::Vector2f(relativePlayerLocation.x - 400, relativePlayerLocation.y + 250);
	healthBarFrame.draw(window);
    //set the fullness of the healthbar based on player health 
    healthBar.setSize(sf::Vector2f(276 * (game.player.health/100), 36));
    //set color of healthbar based on player health
    if (game.player.health > 66) {
        healthBar.setFillColor(sf::Color::Green);
    } else if (game.player.health > 33) {
        healthBar.setFillColor(sf::Color::Yellow);
    } else {
        healthBar.setFillColor(sf::Color::Red);
    }
    healthBar.setPosition(relativePlayerLocation.x - 388, relativePlayerLocation.y + 257);
    window->draw(healthBar);

    /*
    * drawing the weapon selection graphic
    */
    selectedWeapon.position = sf::Vector2f(relativePlayerLocation.x + 300, relativePlayerLocation.y + 200);
    selectedWeapon.updateSprite(game.weapons[game.player.activeWeapon].weaponHUDIndex);
    selectedWeapon.draw(window);

    scoreCount.setPosition(relativePlayerLocation.x - 385, relativePlayerLocation.y - 295);
    int tempScore = int(game.score + 0.5);
    std::string tempScoreString = std::to_string(tempScore);
    scoreCount.setString(tempScoreString);
    window->draw(scoreCount);
    
    // draw ammo counts
    if (game.player.activeWeapon == Game::CHAINSAW_INDEX) {
        ammoCount.setString("");
    }
    else {
        projectileView.rotation = 0.0f;
        projectileView.position = sf::Vector2f(relativePlayerLocation.x + 300, relativePlayerLocation.y + 180);
    
        projectileView.updateSprite(game.projectiles[game.weapons[game.player.activeWeapon].projectileIndex].projectileSpriteIndex);
        projectileView.draw(window);
    
        ammoCount.setPosition(relativePlayerLocation.x + 340, relativePlayerLocation.y + 180);
        
        ammoCount.setString("x " + std::to_string(game.player.ammoCounts[game.player.activeWeapon]));
        
        window->draw(ammoCount);
    } 
}

void SurvivalState::setViewForDrawing() {
    float viewRatio = getViewRatio();
    view.setCenter(sf::Vector2f(std::round(game.player.position.x * getViewRatio()), std::round(game.player.position.y * getViewRatio())));
    window->setView(view);
}

inline float SurvivalState::getViewRatio() const {    
    return game.level.tileLength / Game::TILE_SIZE;
}
