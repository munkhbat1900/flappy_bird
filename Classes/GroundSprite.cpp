//
//  GroundSprite.cpp
//  flappy_bird
//
//  Created by Avirmed Munkhbat on 10/9/14.
//
//

#include "GroundSprite.h"

USING_NS_CC;

GroundSprite* GroundSprite::createGround() {
    GroundSprite* groundSprite = new GroundSprite();
    if (groundSprite && groundSprite->initWithFile(BACKGROUND_GROUND_FILENAME)) {
        groundSprite->initGround();
        groundSprite->autorelease();
        return groundSprite;
    } else {
        CC_SAFE_DELETE(groundSprite);
        return nullptr;
    }
}

void GroundSprite::initGround() {
    scheduleUpdate();
}

void GroundSprite::update(float delta) {
    Vec2 position = this->getPosition();
    this->setPosition(Vec2(position.x - speed * delta, position.y));
}

float GroundSprite::getXPosition() {
    return this->getPosition().x;
}
