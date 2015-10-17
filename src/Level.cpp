#include "Level.hpp"

#include <stdlib.h>
#include <string.h>

// Default constructor

// Default destructor

bool Level::init(char* levelFilePath) {
    FILE* levelFile = fopen(levelFilePath, "r");
    
    if (NULL == levelFile) {
        return false;
    }
    
    bool parseSuccess = parseLevel(levelFile);
    
    fclose(levelFile);
    
    return parseSuccess;
}


// TODO: print to stderr/cerr the exact cause of each failure
bool Level::parseLevel(FILE* levelFile) {
    char buf[256];
    int intBuf[3];
    float tempFloat;
    
    width = -1;
    height = -1;
    tileLength = -1;
    int numTiles = -1;
    
    // while we have not reached the end of the levelFile, read the next token
    while(fscanf(levelFile, "%s", buf) != EOF) {
        // switch on the first character of the line read
        switch(buf[0]) {
            // 'n', number of distinct tiles, do this to easily order Tile vector
            case 'n': 
                printf("Entering n\n");
                fscanf(levelFile, "%d", &numTiles);
                printf("Found num tiles = %d\n\n", numTiles);
                
                // the map needs to use at least one tile
                if (numTiles < 1) {
                    return false;
                }
                
                tileVector.resize(numTiles);
                printf("Exiting n\n");
            break;
            // 's', size of tile, in pixels, assumes a square tile
            case 's':
                printf("Entering s\n");
                fscanf(levelFile, "%d", &tileLength);
                
                // tile length needs to be at least one pixel
                if (tileLength < 1) {
                    return false;
                }
                printf("Exiting s\n");
            break;
            // 'm', width and height of the level in number of tiles
            case 'm':
                printf("Entering m\n");
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
                printf("Exiting m\n");
            break;
            // 'u', uses tile definition. first value is the id the tile will be referenced by. the 2nd and 3rd values are the x and y position on the tile sheet.
            case 'u': 
                printf("Entering u\n");
                fscanf(levelFile, "%d %d %d %s", &intBuf[0], &intBuf[1], &intBuf[2], buf);
                
                // we must have seen the 'n' line
                if (numTiles < 1) {
                    return false;
                }
                
                // we must have seen the the 's' line as well
                if (tileLength < 1) {
                    return false;
                }
                
                // the tile resource num should be between 0 and numTiles - 1
                if (intBuf[0] < 0 || intBuf[0] >= numTiles) {
                    return false;
                }
                
                // TODO: check the x and y position on the tile sheet
                
                {
                    Tile tile;
                    tile.init(buf, intBuf[0], sf::IntRect(intBuf[1], intBuf[2], tileLength, tileLength));
                    tileVector[tile.resourceNum] = tile;
                }
                printf("Exiting u\n");
            break;
            // 't', tile definition: x y tileResourceNum rotation
            case 't':
                printf("Entering t\n");
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
                printf("Exiting t\n");
            break;
            // something else, ignore it
            default:
                printf("Entering default\n %s\n", buf);
                fgets(buf, sizeof(buf), levelFile);
                printf("%s\n Exiting default\n", buf);
            break;
        }
    }
    
    return true;
}
