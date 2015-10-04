#include "ImageView.hpp"

ImageView::ImageView(std::string &spriteSheetPath, int newSpriteWidth, int newSpriteHeight) : position(), spriteWidth(), spriteHeight() {    
    spriteWidth = newSpriteWidth;
    spriteHeight = newSpriteHeight;
    texture.loadFromFile(spriteSheetPath, sf::IntRect(0, 0, spriteWidth, spriteHeight));
    spritesheet.loadFromFile(spriteSheetPath);
    sprite.setTexture(texture);
}


// Default destructor

void ImageView::draw(sf::RenderWindow* window) {
    sprite.setPosition(position);
    window->draw(sprite);
}
