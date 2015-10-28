#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Level.hpp"
#include "SpriteView.hpp"

sf::Vector2i getTilePosition(sf::Vector2f viewPosition, sf::Vector2i mousePosition){
    int mouseX = mousePosition.x;
    int mouseY = mousePosition.y;
    int viewPosX = viewPosition.x;
    int viewPosY = viewPosition.y;
    
    int absX = (viewPosX + (mouseX)) - 400;
    int absY = (viewPosY + (mouseY)) - 300;

    int tilePosX = absX / 128; //TILESIZE
    int tilePosY = absY / 128;

    return sf::Vector2i(tilePosX, tilePosY);
}

int main(int argc, char** argv) {
    unsigned int WINDOW_WIDTH = 800;
    unsigned int WINDOW_HEIGHT = 600;
    std::string LEVEL_TILE_SHEET_FILENAME = "assets/tileset.png";
    std::string LEVEL_FILE = "assets/map.level";
    const std::string LEVEL_FIlE_EXPORT = "assets/exportedLevel.level";
    const char* tileArgs[] = {"grassTile.tile", "webTile.tile", "rockTile.tile", "sandTile.tile", "squareTile.tile",
                              "pentaTile.tile"};
    const std::vector<std::string> TILE_FILEPATHS(tileArgs, tileArgs + 6);
    
    sf::Vector2f position;
    
    sf::View view;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "MapViewer", sf::Style::Titlebar | sf::Style::Close);
    view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    window.setFramerateLimit(60);
    
    SpriteView levelView;
    Level level;

    int curTile = 1;
    sf::Vector2i tilePos;
    sf::Vector2i mousePos;
    
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            factor = 2.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            factor = 4.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            factor = 8.0f;
        }
        
        //update position based on factor and movement vector
        position += moveVector * (factor * baseSpeed);

        //allow for selecting which tile is being placed
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
            curTile = 0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            curTile = 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            curTile = 2;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            curTile = 3;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            curTile = 4;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
            curTile = 5;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
            curTile = 6;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
            curTile = 7;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
            curTile = 8;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
            curTile = 9;
        }

        //handle tile placement
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            mousePos = sf::Mouse::getPosition(window);
            tilePos = getTilePosition(position, mousePos);
            if (tilePos.x < 0 || tilePos.x >= level.width || tilePos.y < 0 || tilePos.y >= level.height) {
                std::printf("out of bounds!");
            } else {
                switch(curTile) {
                    case 0:
                        level.tiles[tilePos.x][tilePos.y].resource = 0;
                        break;
                    case 1:
                        level.tiles[tilePos.x][tilePos.y].resource = 1;
                        break;
                    case 2:
                        level.tiles[tilePos.x][tilePos.y].resource = 2;
                        break;
                    case 3:
                        level.tiles[tilePos.x][tilePos.y].resource = 3;
                        break;
                    case 4:
                        level.tiles[tilePos.x][tilePos.y].resource = 4;
                        break;
                    case 5:
                        level.tiles[tilePos.x][tilePos.y].resource = 5;
                        break;
                    case 6:
                        level.tiles[tilePos.x][tilePos.y].resource = 6;
                        break;
                    case 7:
                        level.tiles[tilePos.x][tilePos.y].resource = 7;
                        break;
                    case 8:
                        level.tiles[tilePos.x][tilePos.y].resource = 8;
                        break;
                    case 9:
                        level.tiles[tilePos.x][tilePos.y].resource = 9;
                        break;
                }
            }
        }
        //handle tile rotation
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            mousePos = sf::Mouse::getPosition(window);
            tilePos = getTilePosition(position, mousePos);
            level.tiles[tilePos.x][tilePos.y].rotation = 0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            mousePos = sf::Mouse::getPosition(window);
            tilePos = getTilePosition(position, mousePos);
            level.tiles[tilePos.x][tilePos.y].rotation = 90;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            mousePos = sf::Mouse::getPosition(window);
            tilePos = getTilePosition(position, mousePos);
            level.tiles[tilePos.x][tilePos.y].rotation = 180;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            mousePos = sf::Mouse::getPosition(window);
            tilePos = getTilePosition(position, mousePos);
            level.tiles[tilePos.x][tilePos.y].rotation = 270;
        }


        //spacebar exports to file
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            level.exportToFile(LEVEL_FIlE_EXPORT, &TILE_FILEPATHS);
        }
        
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
