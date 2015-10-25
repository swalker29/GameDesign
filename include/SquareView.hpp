#ifndef SQUAREVIEW_HPP
#define SQUAREVIEW_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "View.hpp"

// Placeholder view class. Draws a white square.
// Changing this to a circle for now since this is a placeholder class. Don't feel like refactoring the name right now.
class SquareView : public View {
    public:
        sf::Vector2f position;
        float length;
        
        SquareView();
        
        void draw(sf::RenderWindow* window);
        
    private:
        sf::CircleShape rectangle; 
};
#endif
