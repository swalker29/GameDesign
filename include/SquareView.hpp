#ifndef SQUAREVIEW_HPP
#define SQUAREVIEW_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "View.hpp"

// Placeholder view class. Draws a white square.
class SquareView : public View {
    public:
        sf::Vector2f position;
        float length;
        
        SquareView();
        
        void draw(sf::RenderWindow* window);
        
    private:
        sf::RectangleShape rectangle; 
};
#endif
