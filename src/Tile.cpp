#include "Tile.hpp"

#include <stdlib.h>
#include <string.h>

// include the Box2D info too
Tile::Tile(int resourceNum) : resourceNum(resourceNum) {

}

// default destructor?

bool Tile::loadTile(char* tileFilePath) {
    FILE* tileFile = fopen(tileFilePath, "r");
	
	if (NULL == tileFile) {
        return false;
    }
    
	parseTile(tileFile);
	
	fclose(tileFile);
	
	return true;

}

void Tile::parseTile(FILE* tileFile) {
    char buf[256];
	float floatBuf[2];
	float tempFloat;
	
	int width = -1;
	int height = -1;
	
	// initialize Box2D rigid body here
	
	// while we have not reached the end of the tileFile, read the next token
	while(fscanf(tileFile, "%s", buf) != EOF) {
		// switch on the first character of the line read
		switch(buf[0]) {
			// 'i', image used
			// the model shouldn't be concerned about this but for the sake of simplicity, load it here
			case 'i': 
				fgets(buf, sizeof(buf), tileFile);
    			
    			buf[strlen(buf) - 1] = '\0';
				// load image for SFML
				// the string starts at buf + 1 (due to the space)
			break;
			// 'v', vertex of the convex hull for collision. Can be defined in any order because Box2D solves the convex hull problem.
			case 'v':
				fscanf(tileFile, "%f %f", &floatBuf[0], &floatBuf[1]);
				
				// add to the Box2D rigid body here
			break;
			// something else, ignore it
			default:
				fgets(buf, sizeof(buf), tileFile);
			break;
		}
	}
}
