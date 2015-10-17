#include "SpriteView.hpp"

// Default constructor

// Default destructor

bool SpriteView::init(std::string& spriteSheetPath, int newSpriteWidth, int newSpriteHeight) {
    // try to load the texture
    bool result = texture.loadFromFile(spriteSheetPath);
    
    if (result == true) {
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));
        spritesPerRow = texture.getSize().x / newSpriteWidth;
        spriteWidth = newSpriteWidth;
        spriteHeight = newSpriteHeight;
    }
        
    return result;
}

//This is called by the animation controller, who has knowledge of where each frame is.
void SpriteView::updateSprite(int frame) {
    sprite.setTextureRect(sf::IntRect((frame % spritesPerRow) * spriteWidth, (frame / spritesPerRow) * spriteHeight, spriteWidth, spriteHeight));
}

// If the controller knows the bounds of each sprite, it can draw them manually though this
void SpriteView::updateSprite(sf::IntRect rect) {
    sprite.setTextureRect(rect);
}

void SpriteView::draw(sf::RenderWindow* window) {
    sprite.setPosition(position);
    window->draw(sprite);
}
