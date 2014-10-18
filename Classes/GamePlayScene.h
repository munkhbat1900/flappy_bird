//
//  GamePlayScene.h
//  flappy_bird
//
//  Created by Avirmed Munkhbat on 10/10/14.
//
//

#ifndef __GAMEPLAYSCENE_H__
#define __GAMEPLAYSCENE_H__

#include "cocos2d.h"
#include "GroundSprite.h"
#include "BirdSprite.h"

class GamePlayScene : public cocos2d::Layer
{
private:
    void constructBackGround();
    
    // game playing flag
    bool _isGamePlay;
    bool _isDead;
    // game score
    int _score;
    BirdSprite* _birdSprite;
    
    // ground vector
    cocos2d::Vector<GroundSprite*> _groundVector;
    // touch event
    std::function<bool(cocos2d::Touch*, cocos2d::Event*)> onTouchBegan();
    
    void update(float delta);
    
    void createGround();
    bool onContactBegin( cocos2d::PhysicsContact &contact );
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlayScene);
};

#endif
