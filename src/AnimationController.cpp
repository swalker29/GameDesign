#include "AnimationController.hpp"

AnimationController::AnimationController() {

    root = new node;
    root->anim = NULL;
}

void AnimationController::update() {

    conductor = root;
    while (conductor->anim != NULL) {
        conductor->currentFrame++;
        if (conductor->currentFrame > conductor->startFrame + conductor->animLength) {
            conductor->currentFrame = conductor->startFrame;
        }
        conductor->anim->updateSprite(conductor->currentFrame);
        conductor = conductor->next;
    }
}

void AnimationController::addSprite(SpriteView *newSprite, int animLength, int startFrame) {
    conductor = root;
    while (conductor->anim != NULL) {
        conductor = conductor->next;
    }
    conductor->anim = newSprite;
    conductor->animLength = animLength;
    conductor->startFrame = startFrame;
    conductor->currentFrame = startFrame;
    //Create a new node so that a new sprite may be added later.
    conductor->next = new node;
    conductor->next->anim = NULL;
}
