#ifndef IMAGEVIEW_HPP
#define IMAGEVIEW_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include "View.hpp"

// Image View class, used for any non-animated images. The entire texture is displayed when drawn.
class ImageView : public View {
    public:     
        sf::Vector2f position;
        
        // Default constructor
        
        // Default destructor
        
        bool init(std::string& imagePath);

        void draw(sf::RenderWindow* window);

    private:
        sf::Sprite sprite;
        sf::Texture texture;
};
#endif
