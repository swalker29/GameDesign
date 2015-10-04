#ifndef SPRITEVIEW_HPP
#define SPRITEVIEW_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include "View.hpp"

// Sprite View class, used for any animated images. Requires a
// spritesheet 10 sprites wide.
class SpriteView : public View {
    public:
        //Any public variables also go here.
        sf::Image spritesheet;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position;

        int spriteWidth;
        int spriteHeight;
        
        SpriteView(std::string &spriteSheetPath, int newSpriteWidth, int newSpriteHeight);
        void updateSprite(int frame);

        void draw(sf::RenderWindow* window);

    private:
        
};
#endif
