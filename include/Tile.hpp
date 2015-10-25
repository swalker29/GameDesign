#ifndef TILE_HPP
#define TILE_HPP

#include <list>
#include <memory>
#include <SFML/Graphics/Rect.hpp>

class Tile {
    public:
        int tileMapPosition;
        // Box2D stuff
        
        // pathfinding stuff

        
        // Default constructor
        
        // Default descructor
        
        bool init(const char* tileFilePath, int newTileMapPosition, int tileLength, std::list<sf::Vector2f>* meshPoints);
        
    private:
    
        std::list<sf::Vector2f>* meshPoints;
        bool parseTile(FILE* tileFile, int newTileMapPosition, int tileLength);
};
#endif
