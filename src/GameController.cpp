#include "GameController.hpp"

#include <Box2D/Box2D.h>

#include "Utils.hpp"

#define FPS 60

static const std::string FONT_FILENAME = "assets/DroidSans.ttf";
static const std::string LEVEL_TILE_SHEET_FILENAME = "assets/testanimation.png";
static constexpr char* CONTROL_CONFIG_FILENAME = (char*)"assets/config.txt";

GameController::GameController(int argc, char** argv) {

}

GameController::~GameController() {
    if (window != nullptr) {
        delete window;
        window = nullptr;
    }
}

void GameController::run() {    
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
        }
        
        // Leave this here instead of in getInput() because if the controller gets disconnected we should pause.
        sf::Joystick::update();
        useController = sf::Joystick::isConnected(0); //call this inside ControlsConfig

        controlsConfig.getInput(useController, window);
        
        elapsed = clock.restart();
        
        game.update(elapsed.asSeconds(), controlsConfig.input);
        
        // display logic
        
        draw();
    }

    return;
}

void GameController::init() {
    if (!game.init()) {
        fprintf(stderr, "Error initializing game. Program exiting.\n");
        fflush(stdout);
        std::exit(-1);
    }
    
    initViews();
    
    
    // control configuration initialization
    if (!controlsConfig.loadControlsConfig(CONTROL_CONFIG_FILENAME)) {
        printf("Error initializing control configuration. Program exiting.\n"); //TODO: print to stderr
        fflush(stdout);
        std::exit(-1);
    }
    
    // no resize
    view.setSize(GameController::WINDOW_WIDTH, GameController::WINDOW_HEIGHT);
    window = new sf::RenderWindow(sf::VideoMode(GameController::WINDOW_WIDTH, GameController::WINDOW_HEIGHT, 32), "Game", sf::Style::Titlebar | sf::Style::Close);
    //window = new sf::RenderWindow(sf::VideoMode(800,600,32), "Game");
    
    window->setFramerateLimit(60);
}

void GameController::initViews() {
    
    if (!font.loadFromFile(FONT_FILENAME)) {
        fprintf(stderr, "Error: Unable to load font. Program exiting\n");
        std::exit(-1);
    }
    if (!levelView.init(LEVEL_TILE_SHEET_FILENAME, game.level.tileLength, game.level.tileLength)) {
        fprintf(stderr, "Error: Unable to load level tile sheet. Program exiting\n");
        std::exit(-1);
    }
    
    playerView.length = 35.0f;
    enemyView.length = 25.0f;
    playerAim.length = 15.0f;     
}

void GameController::draw() {
    window->clear(sf::Color::Black);

    setViewForDrawing();
    
    drawLevel();
    drawPlayer();
    drawAim();
    drawEnemies();
    
    window->display();
}

void GameController::drawPlayer() {
    float ratio = getViewRatio();
    // TODO: when we switch the player to use SpriteView, draw player centered at game.player.position, currently we use that as the top-left.
    playerView.position = ratio * game.player.position;
    playerView.draw(window);
}

void GameController::drawAim() {
    float ratio = getViewRatio();
    playerAim.position = ratio * (game.player.position + 2.0f * game.player.direction);  
    playerAim.draw(window);
}

void GameController::drawEnemies() {
    float ratio = getViewRatio();
    for (auto& enemy : game.enemies) {
        enemyView.position = ratio * enemy->position;
        enemyView.draw(window);
    }
}

void GameController::drawLevel() {
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
            levelView.position = game.getTilePosition(x, y) * viewRatio;
            levelView.draw(window);
        }
    }    
}

void GameController::setViewForDrawing() {
    view.setCenter(game.player.position * getViewRatio());
    window->setView(view);
}

inline float GameController::getViewRatio() const {    
    return game.level.tileLength / Game::TILE_SIZE;
}
