#ifndef IMAGEVIEW_HPP
#define IMAGEVIEW_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include "View.hpp"

// Image View class, used for any non-animated images. Spritesheet should be a single image, or the image used 
// should be in top left. Size of sprite should be hardcoded at this point.
class ImageView : public View {
    public:
        //Any public variables also go here.
        sf::Image spritesheet;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position;

        int spriteWidth;
        int spriteHeight;
        
        ImageView(std::string &spriteSheetPath, int newSpriteWidth, int newSpriteHeight);

        void draw(sf::RenderWindow* window);

    private:
        
};
#endif
