#ifndef TILE_HPP
#define TILE_HPP

#include <list>
#include <stdio.h>
#include <Box2D/Box2D.h>
#include <SFML/Graphics/Rect.hpp>

#include "PathVertex.hpp"

class Tile {
    public:
        int tileMapPosition;
        
        bool hasCollision;
        bool projectilesCollide;
        
        b2PolygonShape shape;
        
        // pathfinding stuff
        std::vector<std::shared_ptr<PathVertex>> pathVertices;
        
        // Default constructor
        
        // Default descructor
        
        bool init(const char* tileFilePath, int newTileMapPosition, int tileLength, bool doProjectilesCollide);
        
    private:
        bool parseTile(FILE* tileFile, int newTileMapPosition, int tileLength);
};
#endif
