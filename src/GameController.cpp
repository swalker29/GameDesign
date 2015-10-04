#include "GameController.hpp"

#include <Box2D/Box2D.h>

#include "Utils.hpp"

#define FPS 60
#define TILE_PIXEL_SIZE 256.0f

static const std::string FONT_FILENAME = "assets/DroidSans.ttf";

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

    // controls
    // loadControlConfig();
    
    // no resize
    window = new sf::RenderWindow(sf::VideoMode(800,600,32), "Game", sf::Style::Titlebar | sf::Style::Close);
    //window = new sf::RenderWindow(sf::VideoMode(800,600,32), "Game");
    
    window->setFramerateLimit(60);
    
    initViews();

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
        useController = sf::Joystick::isConnected(0);
        
        getInput();
        
        elapsed = clock.restart();
        
        game.update(elapsed.asSeconds(), input);
        
        // display logic
        
        draw();
    }

    return;
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

void GameController::getInput() {
    if (useController) {
        getControllerInput();
    }
    else {
        getMouseAndKeyboardInput();
    }
}

void GameController::getControllerInput() {
    sf::Joystick::Axis verticalMoveAxis = sf::Joystick::Y;
    sf::Joystick::Axis horizontalMoveAxis = sf::Joystick::X;
    sf::Joystick::Axis verticalAimAxis = sf::Joystick::V;
    sf::Joystick::Axis horizontalAimAxis = sf::Joystick::U;
    
    float deadZoneRadius = 25.0f;
    float maxRadius = 100.0f;
    float aimDeadZoneRadius = 50.0f;
    
    // sanity check
    if (sf::Joystick::isConnected(0)) {
        
        unsigned int buttonCount = sf::Joystick::getButtonCount(0);
        
        for (int x = 0; x < buttonCount; x++) {
            if (sf::Joystick::isButtonPressed(0, x)) {
                //printf("Button %d is pressed\n", x);
            }
        }
    }

    // get movement vector (left thumbstick on xbox controller)
    float moveY = sf::Joystick::getAxisPosition(0, verticalMoveAxis);
    float moveX = sf::Joystick::getAxisPosition(0, horizontalMoveAxis);
    
    float length = sqrt(moveX*moveX + moveY*moveY);
    float factor = (length - deadZoneRadius) / (maxRadius - deadZoneRadius);
    
    sf::Vector2f moveVector(0.0f, 0.0f);
    
    if (factor > 0.0f) {
        // if the factor is larger than 1, scale back to make moveVector unit length
        if (factor > 1.0f) {
            factor = 1.0f / factor;
        }
        
        moveVector.x =  factor * moveX / maxRadius;
        moveVector.y = factor * moveY / maxRadius;
    }
    
    // get aim vector (right thumbstick on xbox controller)
    float aimY = sf::Joystick::getAxisPosition(0, verticalAimAxis);
    float aimX = sf::Joystick::getAxisPosition(0, horizontalAimAxis);
    
    length = sqrt(aimX*aimX + aimY*aimY);
    
    sf::Vector2f aimVector(0.0f, 0.0f);
    
    if (length > aimDeadZoneRadius) {
        aimVector.x = aimX;
        aimVector.y = aimY;
        
        normalizeVector2f(aimVector);
    }
    
    // set values in input
    //input.fireWeapon = sf::Joystick::getAxisPosition(fireAxis) > fireAxisThreshold;
    input.movement = moveVector;
    input.aim = aimVector;
}

void GameController::getMouseAndKeyboardInput() {    
    sf::Keyboard::Key moveUp = sf::Keyboard::Up;
    sf::Keyboard::Key moveDown = sf::Keyboard::Down;
    sf::Keyboard::Key moveRight = sf::Keyboard::Right;
    sf::Keyboard::Key moveLeft = sf::Keyboard::Left;
    sf::Mouse::Button fireGun = sf::Mouse::Left;
    
    // get movement vector from keyboard
    sf::Vector2f moveVector(0.0f, 0.0f);
    
    if (sf::Keyboard::isKeyPressed(moveDown)) {
        moveVector.y += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(moveUp)) {
        moveVector.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(moveRight)) {
        moveVector.x += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(moveLeft)) {
        moveVector.x -= 1.0f;
    }
    
    // get aim vector from mouse
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    sf::Vector2u windowSize = window->getSize();
    
    sf::Vector2f aimVector(mousePosition.x - (windowSize.x / 2.0f), mousePosition.y - (windowSize.y / 2.0f));
    
    normalizeVector2f(aimVector);
    normalizeVector2f(moveVector);
    
    // set values in input
    input.fireWeapon = sf::Mouse::isButtonPressed(fireGun);
    input.movement = moveVector;
    input.aim = aimVector;
}

void GameController::initViews() {
    float ratio = getViewRatio();
    
    if (!font.loadFromFile(FONT_FILENAME)) {
        printf("Error: Unable to load font. Program exiting");
        std::exit(-1);
    }
    
    playerView.length = 15.0f;
    enemyView.length = 10.0f;
    playerAim.length = 5.0f;   

    
}

float GameController::getViewRatio() {
    //sf::Vector2f size = window->getView().getSize();
    
    return TILE_PIXEL_SIZE / Game::TILE_SIZE;
}
