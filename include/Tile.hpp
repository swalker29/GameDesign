#ifndef TILE_HPP
#define TILE_HPP

#include <stdio.h>

#include <SFML/Graphics/Rect.hpp>

class Tile {
    public:
    
        int resourceNum;
        
        sf::IntRect spriteBounds;
        
        // Box2D stuff
        
        // pathfinding stuff
        
        // Default constructor
        
        // Default descructor
        
        bool init(char* tileFilePath, int newResourceNum, sf::IntRect newSpriteBounds);
        
    private:
    
        bool parseTile(FILE* tileFile, int tileLength);
};
#endif
