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
	
	// while we have not reached the end of the levelFile, read the next token
	while(fscanf(levelFile, "%s", buf) != EOF) {
		// switch on the first character of the line read
		switch(buf[0]) {
			// 'n', number of distinct tiles, do this to easily order Tile vector
			case 'n': 
				fscanf(levelFile, "%d", &intBuf[0]);
    			
    			// tileVector.resize(intBuf[0]);
			break;
			// 'u', uses tile definition
			case 'u': 
			    fscanf(levelFile, "%d", &intBuf[0]);
				fgets(buf, sizeof(buf), levelFile);
    			
    			buf[strlen(buf) - 1] = '\0';
    			
    			/*
    			 * unsure if this is how we want to do this
    			 {
    			    Tile tile(intBuf[0]);
    			    tile.loadTile(buf + 1);
    			    tileVector[tile.resourceNum] = tile;
    			 }
    			 */
			break;
			// 'w', width, number of tiles in the X direction
			case 'w':
				fscanf(levelFile, "%d", &width);
				
				if (height != -1) {
			        std::vector<TileElement> row(height);
			        
			        for (int x = 0; x < width; x++) {
                        tiles.push_back(row);
                    }
                }
			break;
			// 'h', height, number of tiles in the Y direction
			case 'h': 
				fscanf(levelFile, "%d", &height);
			    
			    if (width != -1) {
			        std::vector<TileElement> row(height);
			        
			        for (int x = 0; x < width; x++) {
                        tiles.push_back(row);
                    }
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
