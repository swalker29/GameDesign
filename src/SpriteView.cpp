#include "SpriteView.hpp"

SpriteView::SpriteView() : length(0.0f), position(), rectangle() {
    rectangle.setFillColor(sf::Color::White);
}

// Default destructor

void SpriteView::draw(sf::RenderWindow* window) {
    rectangle.setSize(sf::Vector2f(length, length));
    rectangle.setPosition(position);
    window->draw(rectangle);
}
