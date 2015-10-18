#ifndef TILE_HPP
#define TILE_HPP

#include <stdio.h>

#include <SFML/Graphics/Rect.hpp>

class Tile {
    public:
        int tileMapPosition;
        // Box2D stuff
        
        // pathfinding stuff
        
        // Default constructor
        
        // Default descructor
        
        bool init(const char* tileFilePath, int newTileMapPosition, int tileLength);
        
    private:
    
        bool parseTile(FILE* tileFile, int tileLength);
};
#endif
