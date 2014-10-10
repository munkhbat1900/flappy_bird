//
//  Animation.cpp
//  flappy_bird
//
//  Created by Avirmed Munkhbat on 10/10/14.
//
//

#include "BirdAnimation.h"

USING_NS_CC;

FiniteTimeAction* BirdAnimation::birdNormalAnimation(BirdType birdType, Vec2 position) {
    std::vector<std::string> imageFileNames = BirdAnimation::getImageFileNames(birdType);
    
    // flying wings animation
    Animation *animation = Animation::create();
    for (std::string fileName : imageFileNames) {
        // should check if this method use cache.
        animation->addSpriteFrameWithFile(fileName);
    }
    animation->setDelayPerUnit(BIRD_FRAME_DELAY);
    
    // up and down animation
    auto downAction = MoveTo::create(BIRD_MOVE_TIME, Vec2(position.x, position.y - BIRD_UP_AND_DOWN_ANIMATION_HEIGHT));
    auto upAction = MoveTo::create(BIRD_MOVE_TIME, Vec2(position.x, position.y + BIRD_UP_AND_DOWN_ANIMATION_HEIGHT));
    auto flyWingAction = Animate::create(animation);
    
    auto spawn1 = Spawn::create(flyWingAction, upAction, NULL);
    auto spawn2 = Spawn::create(flyWingAction, downAction, NULL);
    
    auto sequence = Sequence::create(spawn1, spawn2, NULL);
    
    
    return RepeatForever::create(sequence);
}

std::vector<std::string> BirdAnimation::getImageFileNames(BirdType birdType) {
    std::vector<std::string> imageFiles;
    switch (birdType) {
        case BirdType::BLUE:
            imageFiles.push_back(BLUE_BIRD_FLYUP);
            imageFiles.push_back(BLUE_BIRD_NORMAL);
            imageFiles.push_back(BLUE_BIRD_FLYDOWN);
            return imageFiles;
        case BirdType::RED:
            imageFiles.push_back(RED_BIRD_FLYUP);
            imageFiles.push_back(RED_BIRD_NORMAL);
            imageFiles.push_back(RED_BIRD_FLYDOWN);
            return imageFiles;
        case BirdType::YELLOW:
            imageFiles.push_back(YELLOW_BIRD_FLYUP);
            imageFiles.push_back(YELLOW_BIRD_NORMAL);
            imageFiles.push_back(YELLOW_BIRD_FLYDOWN);
            return imageFiles;
        default:
            assert(false);
    }
}