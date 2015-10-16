#include "Level.hpp"

#include <stdlib.h>
#include <string.h>

// Default constructor

// Default destructor

bool Level::loadLevel(char* levelFilePath) {
    FILE* levelFile = fopen(levelFilePath, "r");
    
    if (NULL == levelFile) {
        return false;
    }
    
    bool retval = parseLevel(levelFile);
    
    fclose(levelFile);
    
    return retval;
}


// TODO: print to sys.err the exact cause of each failure
bool Level::parseLevel(FILE* levelFile) {
    char buf[256];
    int intBuf[3];
    float tempFloat;
    
    width = -1;
    height = -1;
    int tileWidth = -1;
    int tileHeight = -1;
    int numTiles = -1;
    
    // while we have not reached the end of the levelFile, read the next token
    while(fscanf(levelFile, "%s", buf) != EOF) {
        // switch on the first character of the line read
        switch(buf[0]) {
            // 'n', number of distinct tiles, do this to easily order Tile vector
            case 'n': 
                fscanf(levelFile, "%d", &numTiles);
                
                // the map needs to use at least one tile
                if (numTiles < 1) {
                    return false;
                }
                
                tileVector.resize(intBuf[0]);
            break;
            // 's', size of tile, in pixels
            case 's':
                fscanf(levelFile, "%d %d", &tileWidth, &tileHeight);
                
                // tiles need to be at least one pixel wide and tall
                if (tileWidth < 1 || tileHeight < 1) {
                    return false;
                }
            break;
            // 'm', width and height of the level in number of tiles
            case 'm':
                fscanf(levelFile, "%d %d", &width, &height);
                
                // the map needs to be at least one tile wide and tall
                if (width < 1 || height < 1) {
                    return false;
                }
                
                {
                    std::vector<TileElement> row(height);
                    
                    for (int x = 0; x < width; x++) {
                        tiles.push_back(row);
                    }
                }
            break;
            // 'u', uses tile definition. first value is the id the tile will be referenced by. the 2nd and 3rd values are the x and y position on the tile sheet.
            case 'u': 
                fscanf(levelFile, "%d %d %d %s", &intBuf[0], &intBuf[1], &intBuf[2], buf);
                
                // we must have seen the 'n' line
                if (numTiles < 1) {
                    return false;
                }
                
                // we must have seen the the 's' line as well
                if (tileWidth < 1 || tileHeight < 1) {
                    return false;
                }
                
                // the tile resource num should be between 0 and numTiles - 1
                if (intBuf[0] < 0 || intBuf[0] >= numTiles) {
                    return false;
                }
                
                {
                    Tile tile;
                    tile.loadTile(buf, intBuf[0], sf::IntRect(intBuf[1], intBuf[2], tileWidth, tileHeight));
                    tileVector[tile.resourceNum] = tile;
                }
            break;
            // 't', tile definition: x y tileResourceNum rotation
            case 't':
                fscanf(levelFile, "%d %d %d %f", &intBuf[0], &intBuf[1], &intBuf[2], &tempFloat);
                
                // we should have seen the 'm' line
                if ( width < 1 || height < 1) {
                    return false;
                }
                
                // the x and y values need to be between 0 and width/height
                if (intBuf[0] < 0 || intBuf[1] < 0 || intBuf[0] >= width || intBuf[1] >= height) {
                    return false;
                }
                
                tiles[intBuf[0]][intBuf[1]].resource = intBuf[2];
                tiles[intBuf[0]][intBuf[1]].rotation = tempFloat;
            break;
            // something else, ignore it
            default:
                fgets(buf, sizeof(buf), levelFile);
            break;
        }
    }
    
    return true;
}
