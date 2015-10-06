#include "ImageView.hpp"

// Default constructor

// Default destructor

bool ImageView::init(std::string& imagePath) {
    texture.loadFromFile(imagePath);
    sprite.setTexture(texture);
}

void ImageView::draw(sf::RenderWindow* window) {
    sprite.setPosition(position);
    window->draw(sprite);
}
