#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

#include "Tile.hpp"
#include "TileElement.hpp"

class Level {
    public:
    
        std::vector<std::vector<TileElement>> tiles;
        std::vector<Tile> tileVector;
        
        int width;
        int height;
        int tileLength; // in pixels
    
        // Default constructor
        
        // Default destructor
        
        bool init(const std::string& levelFilePath);

        bool exportToFile(const std::string& exportPath, const std::vector<std::string>* tileFilePaths);
    
    private:

        bool parseLevel(FILE* levelFile);
};
#endif

