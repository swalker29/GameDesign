#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <stdio.h>
#include <vector>

#include "TileElement.hpp"

class Level {
    public:
    
        std::vector<std::vector<TileElement>> tiles;
        
        int width, height;
        
        // float tileSize; // Tile size in game coordinates
    
        Level();
        
        bool loadLevel(char* levelFilePath);
    
        //~Level();

    private:
     
        void parseLevel(FILE* levelFile);
};
#endif