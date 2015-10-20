#ifndef ANIMATIONCONTROLLER_HPP
#define ANIMATIONCONTROLLER_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "SpriteView.hpp"

class AnimationController {
    public:
        const float duration = 5; //placeholder number
        float elapsedDuration = duration;
        unsigned int currentFrame;
        std::vector<sf::IntRect> sequence;
        sf::Sprite sprite;

        AnimationController();
        void update();
        void addSprite(SpriteView *newSprite, int animLength, int startFrame);
        void removeSprite(SpriteView *newSprite);
        void drawAll(sf::RenderWindow* window);
        
    private:
        struct node {
            SpriteView *anim;
            int animLength;
            int startFrame;
            int currentFrame;
            node *next;
        };
        node *root;
        node *conductor;
        //node *remover;
        
};
#endif
