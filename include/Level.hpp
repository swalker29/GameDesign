#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "Tile.hpp"
#include "TileElement.hpp"

#define TILESTUB 1

class Level {
    public:
    
        std::vector<std::vector<TileElement>> tiles;
        std::vector<Tile> tileVector;
        std::vector<std::shared_ptr<PathVertex>> pathVertices;
        
        int width;
        int height;
        int tileLength; // in pixels
        
        sf::Vector2f startingPosition;
    
        // Default constructor
        
        // Default destructor
        
        bool init(const std::string& levelFilePath);

        bool exportToFile(const std::string& exportPath, const std::vector<std::string>* tileFilePaths);
        PathVertexP findClosestNode(const sf::Vector2f& location) const;
    
    private:

        bool parseLevel(FILE* levelFile);
};
#endif

