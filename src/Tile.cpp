#include "Tile.hpp"

#include <stdlib.h>
#include <string.h>

// Default constructor
        
// Default descructor

bool Tile::loadTile(char* tileFilePath, int newResourceNum, sf::IntRect newSpriteBounds) {
    resourceNum = newResourceNum;
    spriteBounds = newSpriteBounds;
    
    FILE* tileFile = fopen(tileFilePath, "r");
	
	if (NULL == tileFile) {
        return false;
    }
    
	parseTile(tileFile);
	
	fclose(tileFile);
	tileFile = NULL;
	
	return true;

}

void Tile::parseTile(FILE* tileFile) {
	float floatBuf[2];
	float tempFloat;
	
	int width = -1;
	int height = -1;
	
	// initialize Box2D rigid body here
	
	// while we have not reached the end of the tileFile, read the next token
	while(fscanf(tileFile, "%f %f", &floatBuf[0], &floatBuf[1]) != EOF) {
		// add to the Box2D rigid body here
	}
}
