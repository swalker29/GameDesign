#include "Level.hpp"

#include <cstdio>
#include "Utils.hpp"
#include "Game.hpp"
#include "PathVertex.hpp"
#include <iostream>

// Default constructor

// Default destructor

bool Level::init(const std::string& levelFilePath) {
    std::FILE* levelFile = std::fopen(levelFilePath.c_str(), "r");
    
    if (nullptr == levelFile) {
        fprintf(stderr, "Error: Unable to open file: %s for reading.\n", levelFilePath.c_str());
        return false;
    }
    
    bool parseSuccess = parseLevel(levelFile);
    
    std::fclose(levelFile);

#if TILESTUB
    //stubs out one nav mesh node for each tile center
    for (std::size_t x=0; x < tiles.size(); x++) {
        for (std::size_t y=0; y < tiles[0].size(); y++) {
            sf::Vector2f center = tileCenter(x, y, Game::TILE_SIZE);
            this->pathVertices.push_back(std::make_shared<PathVertex>(center));
        }
    }

    const int rowSize = tiles.size();
    const int rows = tiles[0].size();

    auto inBounds = [rowSize, rows] (int x, int y) {
        if (x < 0 || y < 0) return false;
        if (x >= rows || y >= rowSize) return false;
        return true;
    };

    //{dx, dy}
    std::list<std::pair<int,int>> dirs = {
        {0,1},
        {0,-1},
        {-1,0},
        {1,0}
    };
    //Build stub adjacency list
    for (size_t i=this->pathVertices.size(); i--;) {
        for (auto& dir : dirs) {
            int adjRow = i / rows + dir.first;
            int adjCol = i % rows + dir.second;
            if (inBounds(adjRow, adjCol)) {
                int adj = adjRow * rowSize + adjCol;
                this->pathVertices[i]->neighbors.push_back(this->pathVertices[adj]);
            }
        }
    }
    //for (size_t i=this->pathVertices.size(); i-- > -1;) {
    //    this->pathVertices[i]->neighbors.push_back(this->pathVertices[i-1]);
    //    this->pathVertices[i-1]->neighbors.push_back(this->pathVertices[i]);
    //}

#if 1
    //print adjacency list
    for (auto& pv : this->pathVertices) {
        sf::Vector2f pos = pv->position;
        std::cout << pos.x << " " << pos.y;
        std::cout << " : ";

        for (auto& neighbor : pv->neighbors) {
            sf::Vector2f npos = neighbor->position;
            std::cout << " (" << npos.x << "," << npos.y << ")";
        }
        std::cout << std::endl;
    }
#endif
#endif
    return parseSuccess;
}

PathVertexP Level::findClosestNode(sf::Vector2f& location) {
    return this->pathVertices[4];
}

bool Level::parseLevel(std::FILE* levelFile) {
    char buf[256];
    int intBuf[4];
    float tempFloat;
    
    width = -1;
    height = -1;
    tileLength = -1;
    int numTiles = -1;

    
    // while we have not reached the end of the level file, read the next token
    while(std::fscanf(levelFile, "%s", buf) != EOF) {
        // switch on the first character of the line read
        switch(buf[0]) {
            // 'n', number of distinct tiles, do this to easily order Tile vector
            case 'n': 
                std::fscanf(levelFile, "%d", &numTiles);
                
                // the map needs to use at least one tile
                if (numTiles < 1) {
                    fprintf(stderr, "Error: The map file must use at least one tile.\n");
                    return false;
                }
                
                tileVector.resize(numTiles);
            break;
            // 's', size of tile, in pixels, assumes a square tile
            case 's':
                std::fscanf(levelFile, "%d", &tileLength);
                
                // tile length needs to be at least one pixel
                if (tileLength < 1) {
                    fprintf(stderr, "Error: The length of a tile needs to be at least one pixel.\n");
                    return false;
                }
            break;
            // 'm', width and height of the level in number of tiles
            case 'm':
                std::fscanf(levelFile, "%d %d", &width, &height);
                
                // the map needs to be at least one tile wide and tall
                if (width < 1 || height < 1) {
                    fprintf(stderr, "Error: The level must be at least one tile wide and tall.\n");
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
                    fprintf(stderr, "Error: The map file must define the number of tiles used (n) before a uses tile definition (u).\n");
                    return false;
                }
                
                // we must have seen the the 's' line as well
                if (tileLength < 1) {
                    fprintf(stderr, "Error: The map file must define the tile length (s) before a uses tile definition (u).\n");
                    return false;
                }
                
                // the tile resource num and tile map position should be between 0 and numTiles - 1
                if (intBuf[0] < 0 || intBuf[1] < 0 || intBuf[0] >= numTiles || intBuf[1] >= numTiles) {
                    fprintf(stderr, "Error: The tile resource number and tile map position must be greater than or equal to zero and less than the number of tiles used.\n");
                    return false;
                }
                
                {
                    Tile tile;
                    if (!tile.init(buf, intBuf[1], tileLength)) {
                        fprintf(stderr, "Failed to import Tile file: %s\n.", buf);
                        return false;
                    }
                    tileVector[intBuf[0]] = tile;
                }
            break;
            // 't', tile definition: x y tileResourceNum rotation
            case 't':
                std::fscanf(levelFile, "%d %d %d %d", &intBuf[0], &intBuf[1], &intBuf[2], &intBuf[3]);
                
                // we should have seen the 'm' line
                if ( width < 1 || height < 1) {
                    fprintf(stderr, "Error: The map file must define the size of the dimensions of the level (m) before a tile definition (t).\n");
                    return false;
                }
                
                // the x and y values need to be between 0 and width/height
                if (intBuf[0] < 0 || intBuf[1] < 0 || intBuf[0] >= width || intBuf[1] >= height) {
                    fprintf(stderr, "Error: The tile must be placed within the bounds of the level.\n");
                    return false;
                }
                
                // the rotation should be valid
                if (intBuf[3] < 0 || intBuf[3] > 3) {
                    fprintf(stderr, "Error: The rotation should be an integer between 0 and 3.\n");
                    return false;
                }
                
                tiles[intBuf[0]][intBuf[1]].resource = intBuf[2];
                tiles[intBuf[0]][intBuf[1]].rotation = intBuf[3];
            break;
            // something else, ignore it
            default:
                std::fgets(buf, sizeof(buf), levelFile);
            break;
        }
    }
    
    return true;
}

bool Level::exportToFile(const std::string& exportPath, const std::vector<std::string>* tileFilePaths) {
    std::FILE* levelFile = std::fopen(exportPath.c_str(), "w");
    
    if (nullptr == levelFile) {
        return false;
    }
    printf("# number of tile files this level uses\n");
    printf("n %lu\n", tileVector.size());
    
    printf("\n# size of the tiles in pixels\n");
    printf("s %d\n", tileLength);

    printf("\n# size of the level in tiles\n");
    printf("m %d %d\n", width, height);

    printf("\n# tile files used\n");
    for (int x = 0; x < tileVector.size(); x++) {
        printf("u %d %d %s\n", x, x, (*tileFilePaths)[x].c_str());
    }

    printf("\n# tiles on the map\n");
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            printf("t %d %d %d %d\n", x, y, tiles[x][y].resource, tiles[x][y].rotation);
        }
    }
    fprintf(levelFile, "# number of tile files this level uses\n");
    fprintf(levelFile, "n %lu\n", tileVector.size());
    
    fprintf(levelFile, "\n# size of the tiles in pixels\n");
    fprintf(levelFile, "s %d\n", tileLength);

    fprintf(levelFile, "\n# size of the level in tiles\n");
    fprintf(levelFile, "m %d %d\n", width, height);

    fprintf(levelFile, "\n# tile files used\n");
    for (int x = 0; x < tileVector.size(); x++) {
        fprintf(levelFile, "u %d %d %s\n", x, x, (*tileFilePaths)[x].c_str());
    }

    fprintf(levelFile, "\n# tiles on the map\n");
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            fprintf(levelFile, "t %d %d %d %d\n", x, y, tiles[x][y].resource, tiles[x][y].rotation);
        }
    }
    
    std::fclose(levelFile);
    
    return true;
}
