#ifndef PATHVERTEX_HPP
#define PATHVERTEX_HPP

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

class PathVertex {
    public:
        sf::Vector2f position;
        std::vector<std::shared_ptr<PathVertex>> neighbors;
        // vector of weights?
        
        PathVertex(sf::Vector2f position);
        
        // Default destructor
};
#endif
