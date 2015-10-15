#include "Level.hpp"

#include <stdlib.h>
#include <string.h>

Level::Level() {

}

// default destructor

bool Level::loadLevel(char* levelFilePath) {
    FILE* levelFile = fopen(levelFilePath, "r");
    
    if (NULL == levelFile) {
        return false;
    }
    
    parseLevel(levelFile);
    
    fclose(levelFile);
    
    return true;
}

void Level::parseLevel(FILE* levelFile) {
    char buf[256];
    int intBuf[3];
    float tempFloat;
    
    int width = -1;
    int height = -1;
    int tileWidth = 0;
    int tileHeight = 0;
    
    // while we have not reached the end of the levelFile, read the next token
    while(fscanf(levelFile, "%s", buf) != EOF) {
        // switch on the first character of the line read
        switch(buf[0]) {
            // 'n', number of distinct tiles, do this to easily order Tile vector
            case 'n': 
                fscanf(levelFile, "%d", &intBuf[0]);
                
                tileVector.resize(intBuf[0]);
            break;
            // 's', size of tile
            case 's':
                fscanf(levelFile, "%d %d", &tileWidth, &tileHeight);
            break;
            // 'm', width, number of tiles in the X direction
            case 'm':
                fscanf(levelFile, "%d %d", &width, &height);
                
                {
                    std::vector<TileElement> row(height);
                    
                    for (int x = 0; x < width; x++) {
                        tiles.push_back(row);
                    }
                }
            break;
            // 'u', uses tile definition
            case 'u': 
                fscanf(levelFile, "%d %d %d %s", &intBuf[0], &intBuf[1], &intBuf[2], buf);

                {
                    Tile tile;
                    tile.loadTile(buf, intBuf[0], sf::IntRect(intBuf[1], intBuf[2], tileWidth, tileHeight));
                    tileVector[tile.resourceNum] = tile;
                }
            break;
            // 't', tile definition: x y tileResourceNum rotation
            case 't':
                fscanf(levelFile, "%d %d %d %f", &intBuf[0], &intBuf[1], &intBuf[2], &tempFloat);
                tiles[intBuf[0]][intBuf[1]].resource = intBuf[2];
                tiles[intBuf[0]][intBuf[1]].rotation = tempFloat;
            break;
            // something else, ignore it
            default:
                fgets(buf, sizeof(buf), levelFile);
            break;
        }
    }
}
