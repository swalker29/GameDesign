#include "Level.hpp"

#include <string>
#include <cstdio>

// Default constructor

// Default destructor

bool Level::init(const std::string& levelFilePath, std::list<sf::Vector2f>* meshPoints) {
    std::FILE* levelFile = std::fopen(levelFilePath.c_str(), "r");
    
    if (nullptr == levelFile) {
        return false;
    }
    
    bool parseSuccess = parseLevel(levelFile, meshPoints);
    
    std::fclose(levelFile);
    
    return parseSuccess;
}

// TODO: print to stderr/cerr the exact cause of each failure
bool Level::parseLevel(std::FILE* levelFile, std::list<sf::Vector2f>* meshPoints) {
    char buf[256];
    int intBuf[3];
    float tempFloat;
    
    width = -1;
    height = -1;
    tileLength = -1;
    int numTiles = -1;
    
    // while we have not reached the end of the levelFile, read the next token
    while(std::fscanf(levelFile, "%s", buf) != EOF) {
        // switch on the first character of the line read
        switch(buf[0]) {
            // 'n', number of distinct tiles, do this to easily order Tile vector
            case 'n': 
                std::fscanf(levelFile, "%d", &numTiles);
                
                // the map needs to use at least one tile
                if (numTiles < 1) {
                    return false;
                }
                
                tileVector.resize(numTiles);
            break;
            // 's', size of tile, in pixels, assumes a square tile
            case 's':
                std::fscanf(levelFile, "%d", &tileLength);
                
                // tile length needs to be at least one pixel
                if (tileLength < 1) {
                    return false;
                }
            break;
            // 'm', width and height of the level in number of tiles
            case 'm':
                std::fscanf(levelFile, "%d %d", &width, &height);
                
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
            // 'u', uses tile definition. first value is the id the tile will be referenced by. the 2nd value is the position on the tile sheet.
            case 'u': 
                std::fscanf(levelFile, "%d %d %s", &intBuf[0], &intBuf[1], buf);
                
                // we must have seen the 'n' line
                if (numTiles < 1) {
                    return false;
                }
                
                // we must have seen the the 's' line as well
                if (tileLength < 1) {
                    return false;
                }
                
                // the tile resource num and tile map position should be between 0 and numTiles - 1
                if (intBuf[0] < 0 || intBuf[1] < 0 || intBuf[0] >= numTiles || intBuf[1] >= numTiles) {
                    return false;
                }
                
                {
                    Tile tile;
                    tile.init(buf, intBuf[1], tileLength, meshPoints);
                    tileVector[intBuf[0]] = tile;
                }
            break;
            // 't', tile definition: x y tileResourceNum rotation
            case 't':
                std::fscanf(levelFile, "%d %d %d %f", &intBuf[0], &intBuf[1], &intBuf[2], &tempFloat);
                
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
                std::fgets(buf, sizeof(buf), levelFile);
            break;
        }
    }
    
    return true;
}
