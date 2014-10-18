//
//  BirdSprite.cpp
//  flappy_bird
//
//  Created by Avirmed Munkhbat on 10/10/14.
//
//

#include "BirdSprite.h"
#include "BirdAnimation.h"

USING_NS_CC;

BirdSprite* BirdSprite::createBird() {
    BirdSprite* sprite = new BirdSprite();
    sprite->setRandomBirdType();
    if (sprite && sprite->initWithFile(sprite->getBirdFileName())) {
        sprite->autorelease();
        sprite->scheduleUpdate();
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void BirdSprite::update(float delta) {
//    //if game has already started bird will fall
//    if (_isGameStart && !_isFlyingUp) {
//        auto rotateAction = BirdAnimation::birdRotateDownAnimation();
//        this->runAction(rotateAction);
//    }
}

void BirdSprite::flyUp() {
    _isFlyingUp = true;
}

void BirdSprite::fall() {
    if (!_isFlyingUp) {
        this->setPositionY(this->getPositionY() - BIRD_FALL_SPEED);
    } else {
        this->setPositionY(this->getPositionY() + BIRD_FALL_SPEED);
    }
}

void BirdSprite::animateBirdInStartScene() {
    auto action = BirdAnimation::birdNormalAnimation(_selectedBirdType, this->getPosition());
    this->runAction(action);
}

void BirdSprite::setRandomBirdType() {
    srand((unsigned)time(nullptr));
    
    int birdType = rand() % static_cast<int>(BirdType::COUNT);
    
    _selectedBirdType = static_cast<BirdType>(birdType);
}

std::string BirdSprite::getBirdFileName() {
    switch (_selectedBirdType) {
        case BirdType::BLUE:
            return BLUE_BIRD_NORMAL;
        case BirdType::RED:
            return RED_BIRD_NORMAL;
        case BirdType::YELLOW:
            return YELLOW_BIRD_NORMAL;
        default:
            assert(false);
            break;
    }
}

void BirdSprite::setIsGameStart(bool value) {
    _isGameStart = value;
    // if game has started, stop up and down animation
    if (value) {
        this->stopAllActions();
    }
}

bool BirdSprite::getIsGameStart() {
    return _isGameStart;
}