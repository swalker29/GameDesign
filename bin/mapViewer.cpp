#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Level.hpp"
#include "SpriteView.hpp"

int main(int argc, char** argv) {
    // no resize
    unsigned int WINDOW_WIDTH = 800;
    unsigned int WINDOW_HEIGHT = 600;
    std::string LEVEL_TILE_SHEET_FILENAME = "assets/testanimation.png";
    
    sf::View view;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Game", sf::Style::Titlebar | sf::Style::Close);
    view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    window.setFramerateLimit(60);
    
    SpriteView levelView;
    
    /*
    if (!levelView.init(LEVEL_TILE_SHEET_FILENAME, game.level.tileLength, game.level.tileLength)) {
        fprintf(stderr, "Error: Unable to load level tile sheet. Program exiting\n");
        std::exit(-1);
    }
    */
    
    Level level;
    
    
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
        
        
        // draw the level
        window.clear(sf::Color::Black);
        //view.setCenter(game.player.position * getViewRatio());
        window.setView(view);
    }
    
    
    
    
    
    
    return 0;
}
