#include "SpriteView.hpp"

// Default constructor

// Default destructor

bool SpriteView::init(const std::string& spriteSheetPath, int newSpriteWidth, int newSpriteHeight) {
    // try to load the texture
    bool result = texture.loadFromFile(spriteSheetPath);
    
    texture.setSmooth(false);
    
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

void SpriteView::draw(sf::RenderWindow* window) {
    sprite.setPosition(position + sf::Vector2f(spriteWidth/2, spriteHeight/2));
    sprite.setOrigin(spriteWidth / 2, spriteHeight / 2);
    sprite.rotate(rotation);
    window->draw(sprite);
    sprite.rotate(-rotation);
}
