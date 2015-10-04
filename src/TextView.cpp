#include "TextView.hpp"

TextView::TextView(const sf::Font& font) : text() {
    text.setFont(font);
}

// Default destructor

void TextView::draw(sf::RenderWindow* window) {
    text.setCharacterSize(size);
    text.setPosition(position);
    text.setString(textString);
    window->draw(text);
}
