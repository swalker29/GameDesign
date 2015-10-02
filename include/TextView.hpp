#ifndef TEXTVIEW_HPP
#define TEXTVIEW_HPP

#include <string>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "View.hpp"

class TextView : public View {
    public:
        sf::Vector2f position;
        unsigned int size;
        std::string textString;
        
        TextView(const sf::Font& font);
        
        void draw(sf::RenderWindow* window);
        
    private:
        sf::Text text;

};
#endif
