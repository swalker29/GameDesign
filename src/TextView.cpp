#include "TextView.hpp"

// Default constructor

// Default destructor

bool TextView::init(const sf::Font& font) {
    text.setFont(font);
    
    return true;
}

void TextView::draw(sf::RenderWindow* window) {
    text.setCharacterSize(size);
    text.setPosition(position);
    text.setString(textString);
    window->draw(text);
}
