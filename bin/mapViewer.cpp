#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Level.hpp"
#include "SpriteView.hpp"
#include "math.h"

sf::Vector2i getTilePosition(sf::Vector2f viewPosition, sf::Vector2i mousePosition){
    int mouseX = mousePosition.x;
    int mouseY = mousePosition.y;
    int viewPosX = viewPosition.x;
    int viewPosY = viewPosition.y;
    
    int absX = (viewPosX + (mouseX)) - 400;
    int absY = (viewPosY + (mouseY)) - 300;

    int tilePosX = absX / 256; //TILESIZE
    int tilePosY = absY / 256;

    return sf::Vector2i(tilePosX, tilePosY);
}

int main(int argc, char** argv) {
    unsigned int WINDOW_WIDTH = 800;
    unsigned int WINDOW_HEIGHT = 600;
    std::string LEVEL_TILE_SHEET_FILENAME = "assets/tileset.png";
    std::string LEVEL_FILE = "assets/mapEditorLevel.level";
    const std::string LEVEL_FIlE_EXPORT = "assets/mapEditorLevel.level";
    const char* tileArgs[] = {"assets/TileData/redGrass.tile", "assets/TileData/redGrassWebTL.tile", "assets/TileData/redGrassWebT.tile",
                              "assets/TileData/redGrassWebTR.tile", "assets/TileData/redGrassWebML.tile", "assets/TileData/redGrassWebM.tile",
                              "assets/TileData/redGrassWebMR.tile", "assets/TileData/redGrassWebBL.tile", "assets/TileData/redGrassWebB.tile",
                              "assets/TileData/redGrassWebBR.tile", "assets/TileData/spikyBush.tile", "assets/TileData/spikyTree.tile",
                              "assets/TileData/water.tile", "assets/TileData/waterBubble.tile"};
    const std::vector<std::string> TILE_FILEPATHS(tileArgs, tileArgs + 14);
    
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            curTile = 10;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            curTile = 11;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            curTile = 12;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            curTile = 13;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            curTile = 14;
        }


        //handle tile placement
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            mousePos = sf::Mouse::getPosition(window);
            tilePos = getTilePosition(position, mousePos);
            if (tilePos.x < 0 || tilePos.x >= level.width || tilePos.y < 0 || tilePos.y >= level.height) {

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
                    case 10:
                        level.tiles[tilePos.x][tilePos.y].resource = 10;
                        break;
                    case 11:
                        level.tiles[tilePos.x][tilePos.y].resource = 11;
                        break;
                    case 12:
                        level.tiles[tilePos.x][tilePos.y].resource = 12;
                        break;
                    case 13:
                        level.tiles[tilePos.x][tilePos.y].resource = 13;
                        break;
                    case 14:
                        level.tiles[tilePos.x][tilePos.y].resource = 14;
                        break;
                }
            }
        }
        //handle tile rotation
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt)){
            mousePos = sf::Mouse::getPosition(window);
            tilePos = getTilePosition(position, mousePos);
            level.tiles[tilePos.x][tilePos.y].rotation += 90;
            if (level.tiles[tilePos.x][tilePos.y].rotation == 360) {
                
            }
        }


        //spacebar exports to file
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            level.exportToFile(LEVEL_FIlE_EXPORT, &TILE_FILEPATHS);
            window.clear(sf::Color::White);
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
