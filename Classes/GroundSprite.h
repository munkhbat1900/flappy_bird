#ifndef __GROUNDSPRITE_H__
#define __GROUNDSPRITE_H__

#include "cocos2d.h"
#include "Consts.h"

class GroundSprite : public cocos2d::Sprite {
private:
    void update(float delta);
    // ground move speed
    float speed = 70.0f;
    
public:
    static GroundSprite* createGround();
    GroundSprite() {}
    ~GroundSprite() {}
    
    void initGround();
    
    float getXPosition();
};

#endif