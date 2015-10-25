#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Level.hpp"
#include "SpriteView.hpp"

int main(int argc, char** argv) {
    unsigned int WINDOW_WIDTH = 800;
    unsigned int WINDOW_HEIGHT = 600;
    std::string LEVEL_TILE_SHEET_FILENAME = "assets/testanimation.png";
    std::string LEVEL_FILE = "assets/map.level";
    
    sf::Vector2f position;
    
    sf::View view;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "MapViewer", sf::Style::Titlebar | sf::Style::Close);
    view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    window.setFramerateLimit(60);
    
    SpriteView levelView;
    Level level;
    
    if (!level.init(LEVEL_FILE)) {
        fprintf(stderr, "Error: Unable to load level. Program exiting\n");
        std::exit(-1);
    }
    
    if (!levelView.init(LEVEL_TILE_SHEET_FILENAME, level.tileLength, level.tileLength)) {
        fprintf(stderr, "Error: Unable to load level tile sheet. Program exiting\n");
        std::exit(-1);
    }    
    
    // start main loop
    while(window.isOpen()) {
        // process events
        sf::Event event;
        
        while(window.pollEvent(event)) {
            // Exit
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        // get movement vector from keyboard
        sf::Vector2f moveVector(0.0f, 0.0f);
        float factor = 1.0f;
        float baseSpeed = 5.0f;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            moveVector.y += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            moveVector.y -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            moveVector.x += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            moveVector.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            factor = 2.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            factor = 2.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            factor = 4.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
            factor = 8.0f;
        }
        
        position += moveVector * (factor * baseSpeed);
        
        // draw the level
        window.clear(sf::Color::Black);
        view.setCenter(position);
        window.setView(view);
        
        // TODO: get a better number than 5 for what to draw around the player based on tile size and game window
        int xLow = std::max(0, int(position.x / level.tileLength) - 5) ;
        int xHigh = std::min(level.width - 1, int(position.x / level.tileLength) + 5);
        int yLow = std::max(0, int(position.y / level.tileLength) - 5);
        int yHigh = std::min(level.height - 1, int(position.y / level.tileLength) + 5);
        
        for (int x = xLow; x <= xHigh; x++) {
            for (int y = yLow; y <= yHigh; y++) {
                levelView.updateSprite(level.tileVector[level.tiles[x][y].resource].tileMapPosition);
                levelView.position = sf::Vector2f(x * level.tileLength, y * level.tileLength);
                levelView.draw(&window);
            }
        }
        
        window.display();
    }
    
    return 0;
}
