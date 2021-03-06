#ifndef __GAMESTARTSCENE_H__
#define __GAMESTARTSCENE_H__

#include "cocos2d.h"
#include "GroundSprite.h"

class GameStartScene : public cocos2d::Layer
{
private:
    void constructBackGround();
    
    void update(float delta);
    
    // ground vector
    cocos2d::Vector<GroundSprite*> groundVector;
    
    // start button tap event
    void onStartTap(Ref* sender);
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameStartScene);
};

#endif
