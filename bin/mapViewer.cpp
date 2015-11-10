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
    const std::string LEVEL_FIlE_EXPORT = "assets/mapEditorLevelExport.level";
    const char* tileArgs[] = {"assets/TileData/redGrass.tile", "assets/TileData/redGrassWebTL.tile", "assets/TileData/redGrassWebT.tile",
                              "assets/TileData/redGrassWebTR.tile", "assets/TileData/redGrassWebML.tile", "assets/TileData/redGrassWebM.tile",
                              "assets/TileData/redGrassWebMR.tile", "assets/TileData/redGrassWebBL.tile", "assets/TileData/redGrassWebB.tile",
                              "assets/TileData/redGrassWebBR.tile", "assets/TileData/spikyBush.tile", "assets/TileData/spikyTree.tile",
                              "assets/TileData/spikyBush.tile", "assets/TileData/noCollisionTile.tile", "assets/TileData/noCollisionTile.tile",
                              "assets/TileData/spikyBush.tile", "assets/TileData/noCollisionTile.tile", "assets/TileData/noCollisionTile.tile",
                              "assets/TileData/spikyBush.tile", "assets/TileData/spikyBush.tile", "assets/TileData/noCollisionTile.tile",
                              "assets/TileData/noCollisionTile.tile", "assets/TileData/noCollisionTile.tile", "assets/TileData/noCollisionTile.tile", 
                              "assets/TileData/water.tile", "assets/TileData/water.tile", "assets/TileData/waterBL.tile", 
                              "assets/TileData/waterB.tile", "assets/TileData/waterBR.tile", "assets/TileData/waterL.tile",
                              "assets/TileData/waterR.tile",
                              "assets/TileData/waterTL.tile", "assets/TileData/waterT.tile", "assets/TileData/waterTR.tile",
                              "assets/TileData/noCollisionTile.tile", "assets/TileData/noCollisionTile.tile", "assets/TileData/noCollisionTile.tile",
                              "assets/TileData/noCollisionTile.tile", "assets/TileData/noCollisionTile.tile", "assets/TileData/noCollisionTile.tile",
                              "assets/TileData/noCollisionTile.tile", "assets/TileData/noCollisionTile.tile", "assets/TileData/noCollisionTile.tile",
                              "assets/TileData/noCollisionTile.tile", "assets/TileData/noCollisionTile.tile", "assets/TileData/noCollisionTile.tile"};
    const std::vector<std::string> TILE_FILEPATHS(tileArgs, tileArgs + 46);
    
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
            if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::M){
                    curTile = curTile + 1;
                }
                if(event.key.code == sf::Keyboard::N){
                    curTile = curTile - 1;
                }
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            curTile = 15;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
            curTile = 16;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            curTile = 17;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            curTile = 18;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            curTile = 19;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            curTile = 20;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            curTile = 21;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            curTile = 22;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            curTile = 23;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            curTile = 24;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
            curTile = 25;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
            curTile = 26;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            curTile = 27;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            curTile = 28;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            curTile = 29;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            curTile = 30;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            curTile = 31;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            curTile = 32;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            curTile = 33;
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
                    case 15:
                        level.tiles[tilePos.x][tilePos.y].resource = 15;
                        break;
                    case 16:
                        level.tiles[tilePos.x][tilePos.y].resource = 16;
                        break;
                    case 17:
                        level.tiles[tilePos.x][tilePos.y].resource = 17;
                        break;
                    case 18:
                        level.tiles[tilePos.x][tilePos.y].resource = 18;
                        break;
                    case 19:
                        level.tiles[tilePos.x][tilePos.y].resource = 19;
                        break;
                    case 20:
                        level.tiles[tilePos.x][tilePos.y].resource = 20;
                        break;
                    case 21:
                        level.tiles[tilePos.x][tilePos.y].resource = 21;
                        break;
                    case 22:
                        level.tiles[tilePos.x][tilePos.y].resource = 22;
                        break;
                    case 23:
                        level.tiles[tilePos.x][tilePos.y].resource = 23;
                        break;
                    case 24:
                        level.tiles[tilePos.x][tilePos.y].resource = 24;
                        break;
                    case 25:
                        level.tiles[tilePos.x][tilePos.y].resource = 25;
                        break;
                    case 26:
                        level.tiles[tilePos.x][tilePos.y].resource = 26;
                        break;
                    case 27:
                        level.tiles[tilePos.x][tilePos.y].resource = 27;
                        break;
                    case 28:
                        level.tiles[tilePos.x][tilePos.y].resource = 28;
                        break;
                    case 29:
                        level.tiles[tilePos.x][tilePos.y].resource = 29;
                        break;
                    case 30:
                        level.tiles[tilePos.x][tilePos.y].resource = 30;
                        break;
                    case 31:
                        level.tiles[tilePos.x][tilePos.y].resource = 31;
                        break;
                    case 32:
                        level.tiles[tilePos.x][tilePos.y].resource = 32;
                        break;
                    case 33:
                        level.tiles[tilePos.x][tilePos.y].resource = 33;
                        break;
                    case 34:
                        level.tiles[tilePos.x][tilePos.y].resource = 34;
                        break;
                    case 35:
                        level.tiles[tilePos.x][tilePos.y].resource = 35;
                        break;
                    case 36:
                        level.tiles[tilePos.x][tilePos.y].resource = 36;
                        break;
                    case 37:
                        level.tiles[tilePos.x][tilePos.y].resource = 37;
                        break;
                    case 38:
                        level.tiles[tilePos.x][tilePos.y].resource = 38;
                        break;
                    case 39:
                        level.tiles[tilePos.x][tilePos.y].resource = 39;
                        break;
                    case 40:
                        level.tiles[tilePos.x][tilePos.y].resource = 40;
                        break;
                    case 41:
                        level.tiles[tilePos.x][tilePos.y].resource = 41;
                        break;
                    case 42:
                        level.tiles[tilePos.x][tilePos.y].resource = 42;
                        break;
                    case 43:
                        level.tiles[tilePos.x][tilePos.y].resource = 43;
                        break;
                    case 44:
                        level.tiles[tilePos.x][tilePos.y].resource = 44;
                        break;
                    case 45:
                        level.tiles[tilePos.x][tilePos.y].resource = 45;
                        break;
                    case 46:
                        level.tiles[tilePos.x][tilePos.y].resource = 46;
                        break;
                    case 47:
                        level.tiles[tilePos.x][tilePos.y].resource = 47;
                        break;

                }
            }
        }
        //handle tile rotation
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt)){
            mousePos = sf::Mouse::getPosition(window);
            tilePos = getTilePosition(position, mousePos);
            level.tiles[tilePos.x][tilePos.y].rotation += 1;
            if (level.tiles[tilePos.x][tilePos.y].rotation == 4) {
                level.tiles[tilePos.x][tilePos.y].rotation = 0;
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
