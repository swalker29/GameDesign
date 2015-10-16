#include <stdio.h>

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

void AnimationController::removeSprite(SpriteView *deadSprite) {
    conductor = root;
    //Just iterate through list until memory address matches.
    //The edge case in which the only animation is the one to be removed
    if (conductor->anim == deadSprite) {
        conductor->anim = NULL;
    } else {
        while (conductor->next->anim != deadSprite && conductor->next->anim != NULL) {
            conductor = conductor->next;
        }
        if (conductor->next->anim == NULL) {
            //The sprite doesn't exist.
            fprintf(stderr, "Animation Controller can't find the requested sprite for removal!");
        } else {
            //At this point, conductor->next->anim is deadSprite. Or code is borked.
            //remover = conductor;
            conductor->next = conductor->next->next;
            //does this require special removal to avoid mem leaks?        
        }

    }
}
