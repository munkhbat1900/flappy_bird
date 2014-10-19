#ifndef __BIRDSPRITE_H__
#define __BIRDSPRITE_H__

#include "cocos2d.h"
#include "Consts.h"

class BirdSprite : public cocos2d::Sprite {
private:
    BirdType _selectedBirdType;
    bool _isFlyingUp;
    
public:
    BirdSprite(){}
    ~BirdSprite(){}
    static BirdSprite* createBird();
    
    void setRandomBirdType();
    std::string getBirdFileName();
    
    void animateBirdInStartScene();
    
    void gameStart();
    
    void flyUp();
    
    void stopFlying();
    
    void swingAnimation();
};

#endif