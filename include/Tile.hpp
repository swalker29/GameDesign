#ifndef TILE_HPP
#define TILE_HPP

#include <stdio.h>

class Tile {
    public:
    
        int resourceNum;
        
        // Box2D stuff
        
        Tile(int resourceNum);
        
        bool loadTile(char* tileFilePath);
        
    private:
    
        void parseTile(FILE* tileFile);
};
#endif
