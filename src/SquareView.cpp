#include "SquareView.hpp"

SquareView::SquareView() : length(0.0f), position(), rectangle() {
    rectangle.setFillColor(sf::Color::White);
}

// Default destructor

void SquareView::draw(sf::RenderWindow* window) {
    rectangle.setRadius(length);
    rectangle.setPosition(position);
    window->draw(rectangle);
}
