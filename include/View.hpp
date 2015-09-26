#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

class View {
    public:
        virtual void draw(sf::RenderWindow* window) = 0;
};
#endif
