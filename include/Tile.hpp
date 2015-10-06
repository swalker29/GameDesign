#ifndef TILE_HPP
#define TILE_HPP

#include <stdio.h>

#include <SFML/Graphics/Rect.hpp>

class Tile {
    public:
    
        int resourceNum;
        
        sf::IntRect spriteBounds;
        
        // Box2D stuff
        
        // Default constructor
        
        // Default descructor
        
        bool loadTile(char* tileFilePath, int newResourceNum, sf::IntRect newSpriteBounds);
        
    private:
    
        void parseTile(FILE* tileFile);
};
#endif
