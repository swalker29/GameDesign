#include "Tile.hpp"

#include <cstdio>
#include <memory>
#include <string>

#include "Game.hpp"

// Default constructor
        
// Default descructor

bool Tile::init(const char* tileFilePath, int newTileMapPosition, int tileLength, bool doProjectilesCollide) {
    tileMapPosition = newTileMapPosition;
    projectilesCollide = doProjectilesCollide;
    
    std::FILE* tileFile = std::fopen(tileFilePath, "r");
	
	if (nullptr == tileFile) {
	    fprintf(stderr, "Error: Unable to open file: %s for reading.\n", tileFilePath);
        return false;
    }
    
	bool parseSuccess = parseTile(tileFile, newTileMapPosition, tileLength);
	
	std::fclose(tileFile);

	return parseSuccess;
}

bool Tile::parseTile(std::FILE* tileFile, int newTileMapPosition, int tileLength) {
	char buf[256];
	int intBuf[2];
	
	b2Vec2 vertices[8];
	int count = 0;
	
	// while we have not reached the end of the tileFile, read the next token
    while(std::fscanf(tileFile, "%s", buf) != EOF) {
        // switch on the first character of the line read
        switch(buf[0]) {
            // 'h', point on the collision convex hull
            case 'h': 
                std::fscanf(tileFile, "%d %d", &intBuf[0], &intBuf[1]);
                
                // the points should be within the bounds of the sprite
                if (intBuf[0] < 0 || intBuf[1] < 0 || intBuf[0] >= tileLength || intBuf[1] >= tileLength) {
                    fprintf(stderr, "Error: The location of a collision vertex must be within the bounds of the tile.\n");
                    return false;
                }
                
                {
                    // add to Box2D hull
                    float x = ((float) intBuf[0] / tileLength) * Game::TILE_SIZE;
                    float y = ((float) intBuf[1] / tileLength) * Game::TILE_SIZE;
                    vertices[count++].Set(x, y);
                }
            break;
            // 'v', vertex for pathfinding
            case 'v':
                std::fscanf(tileFile, "%d %d", &intBuf[0], &intBuf[1]);
                
                // the points should be within the bounds of the sprite
                if (intBuf[0] < 0 || intBuf[1] < 0 || intBuf[0] >= tileLength || intBuf[1] >= tileLength) {
                    fprintf(stderr, "Error: The location of a pathfinding vertex must be within the bounds of the tile.\n");
                    return false;
                }
                
                // add to pathfinding vertex here
                {
                    float x = ((float) intBuf[0] / tileLength) * Game::TILE_SIZE;
                    float y = ((float) intBuf[1] / tileLength) * Game::TILE_SIZE;
                    pathVertices.push_back(std::make_shared<PathVertex>(sf::Vector2f(x, y)));
                }
            break;
            // 'e', edge for pathfinding
            case 'e':
                std::fscanf(tileFile, "%d %d", &intBuf[0], &intBuf[1]);
                
                // the vertex values should be valid
                if (intBuf[0] < 0 || intBuf[1] < 0 || intBuf[0] >= pathVertices.size() || intBuf[1] >= pathVertices.size()) {
                    fprintf(stderr, "Error: The pathfinding vertex index must be greater than or equal to zero and less than the total number of pathfinding vertices.\n");
                    return false;
                }
                
                // the edge should be valid, v1 and v2 should be different
                if (intBuf[0] == intBuf[1]) {
                    fprintf(stderr, "Error: The two pathfinding vertices must be unique.\n");
                    return false;
                }
                
                // we should not have seen this edge before
                
                
                // add to pathfinding edge here
                pathVertices[intBuf[0]]->neighbors.push_back(pathVertices[intBuf[1]]);
                pathVertices[intBuf[1]]->neighbors.push_back(pathVertices[intBuf[0]]);
                
            break;
            // something else, ignore it
            default:
                std::fgets(buf, sizeof(buf), tileFile);
            break;
        }
    }
    
    // final box2d stuff
    if (count < 3) {
        hasCollision = false;
    }
    else {
        hasCollision = true;
        shape.Set(vertices, count);
    }
    
    return true;
}
