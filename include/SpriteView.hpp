#ifndef SPRITEVIEW_HPP
#define SPRITEVIEW_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include "View.hpp"

// Sprite View class, used for any animated images. Requires a rectangular spritesheet.
class SpriteView : public View {
    public:
        sf::Vector2f position;
        
        // Default constructor
        
        // Default destructor
        
        bool init(std::string& spriteSheetPath, int newSpriteWidth, int newSpriteHeight);
        
        void updateSprite(int frame);

        void draw(sf::RenderWindow* window);

    private:
        sf::Sprite sprite;
        sf::Texture texture;
        
        int spriteWidth;
        int spriteHeight;
        int spritesPerRow;
};
#endif
