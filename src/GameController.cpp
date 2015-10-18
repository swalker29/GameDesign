#include "GameController.hpp"

#include <Box2D/Box2D.h>

#include "Utils.hpp"

#define FPS 60
#define TILE_PIXEL_SIZE 256.0f

static const std::string FONT_FILENAME = "assets/DroidSans.ttf";
static char* CONTROL_CONFIG_FILENAME = (char *)"assets/config.txt"; //not sure why I can't make this a const

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
        printf("Error initializing game. Program exiting.\n"); // TODO: print to stderr
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
    window = new sf::RenderWindow(sf::VideoMode(800,600,32), "Game", sf::Style::Titlebar | sf::Style::Close);
    //window = new sf::RenderWindow(sf::VideoMode(800,600,32), "Game");
    
    window->setFramerateLimit(60);
}

void GameController::initViews() {
    float ratio = getViewRatio();
    
    if (!font.loadFromFile(FONT_FILENAME)) {
        printf("Error: Unable to load font. Program exiting"); // TODO: print to stderr
        std::exit(-1);
    }
    
    playerView.length = 15.0f;
    enemyView.length = 10.0f;
    playerAim.length = 5.0f;     
}

void GameController::draw() {
    window->clear(sf::Color::Black);

    drawPlayer();
    drawAim();
    drawEnemies();
    
    window->display();
}

void GameController::drawPlayer() {
    float ratio = getViewRatio();
    playerView.position = ratio * game.player.position;
    playerView.draw(window);
}

void GameController::drawAim() {
    float ratio = getViewRatio();
    playerAim.position = ratio * (game.player.position + 0.5f * game.player.direction);  
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
    
}

inline float GameController::getViewRatio() const {    
    return TILE_PIXEL_SIZE / Game::TILE_SIZE;
}

sf::Vector2f GameController::gameToViewCoordinates(const sf::Vector2f& gameCoords) const {
    sf::Vector2f centerScreen = window->getView().getSize() / 2.0f;     
    sf::Vector2f offset = gameCoords - game.player.position;
    offset *= getViewRatio();
    
    return centerScreen + offset;
}
