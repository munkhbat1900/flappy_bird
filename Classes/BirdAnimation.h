//
//  Animation.h
//  flappy_bird
//
//  Created by Avirmed Munkhbat on 10/10/14.
//
//

#ifndef __BIRDANIMATION_H__
#define __BIRDANIMATION_H__

#include "cocos2d.h"
#include "Consts.h"

class BirdAnimation {
public:
    static cocos2d::FiniteTimeAction* birdNormalAnimation(BirdType birdType, cocos2d::Vec2 position);
    static std::vector<std::string> getImageFileNames(BirdType birdType);
    // flying to upper animation
    //static cocos2d::FiniteTimeAction* birdFlyUpAnimation(BirdType birdType, cocos2d::Vec2 position);
    static cocos2d::FiniteTimeAction* birdRotateDownAnimation();
};

#endif
