#include "SpriteView.hpp"

SpriteView::SpriteView(std::string &spriteSheetPath, int newSpriteWidth, int newSpriteHeight) : position(), spriteWidth(), spriteHeight() {
    
    spritesheet.loadFromFile(spriteSheetPath);
    spriteWidth = newSpriteWidth;
    spriteHeight = newSpriteHeight;
}




//This is called by the animation controller, who has knowledge of where each frame is.
void SpriteView::updateSprite(int frame) {
    //Assumes a sprite map width of 10.
    texture.loadFromImage(spritesheet, sf::IntRect((frame % 10)*spriteWidth, (frame / 10)*spriteHeight, spriteWidth,   spriteHeight));
    sprite.setTexture(texture);
}

// Default destructor

void SpriteView::draw(sf::RenderWindow* window) {
    sprite.setPosition(position);
    window->draw(sprite);
}
