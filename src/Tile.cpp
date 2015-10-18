#include "Tile.hpp"

#include <stdlib.h>
#include <string.h>

// Default constructor
        
// Default descructor

bool Tile::init(const char* tileFilePath, int newTileMapPosition, int tileLength) {
    tileMapPosition = newTileMapPosition;
    
    std::FILE* tileFile = std::fopen(tileFilePath, "r");
	
	if (nullptr == tileFile) {
        return false;
    }
    
	bool parseSuccess = parseTile(tileFile, tileLength);
	
	std::fclose(tileFile);
	
	return parseSuccess;

}

// TODO: print to stderr/cerr the exact cause of each failure
bool Tile::parseTile(std::FILE* tileFile, int tileLength) {
	char buf[256];
	int intBuf[2];
	
	// initialize Box2D rigid body here
	
	// while we have not reached the end of the tileFile, read the next token
    while(std::fscanf(tileFile, "%s", buf) != EOF) {
        // switch on the first character of the line read
        switch(buf[0]) {
            // 'h', point on the collision convex hull
            case 'h': 
                std::fscanf(tileFile, "%d, %d", &intBuf[0], &intBuf[1]);
                
                // the points should be within the bounds of the sprite
                if (intBuf[0] < 0 || intBuf[1] < 0 || intBuf[0] >= tileLength || intBuf[1] >= tileLength) {
                    return false;
                }
                
                // add to Box2D hull here
            break;
            // 'v', vertex for pathfinding
            case 'v':
                std::fscanf(tileFile, "%d, %d", &intBuf[0], &intBuf[1]);
                
                // the points should be within the bounds of the sprite
                if (intBuf[0] < 0 || intBuf[1] < 0 || intBuf[0] >= tileLength || intBuf[1] >= tileLength) {
                    return false;
                }
                
                // add to pathfinding vertex here
            break;
            // 'e', edge for pathfinding
            case 'e':
                std::fscanf(tileFile, "%d, %d", &intBuf[0], &intBuf[1]);
                
                // the vertex values should be valid
                if (intBuf[0] < 0 || intBuf[1] < 0) { // || intBuf[0] >= vertexVector.size() || intBuf[1] >= vertexVector.size()
                    return false;
                }
                
                // the edge should be valid, v1 and v2 should be different
                if (intBuf[0] == intBuf[1]) {
                    return false;
                }
                
                // we should not have seen this edge or its inverse before, the graph is undirected
                
                
                // add to pathfinding edge here
            break;
            // something else, ignore it
            default:
                std::fgets(buf, sizeof(buf), tileFile);
            break;
        }
    }
    
    return true;
}
