//
//  GamePlayScene.cpp
//  flappy_bird
//
//  Created by Avirmed Munkhbat on 10/10/14.
//
//

#include "GamePlayScene.h"

USING_NS_CC;

Scene* GamePlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePlayScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    constructBackGround();
    
    scheduleUpdate();
    
    _isGamePlay = false;
    
    _score = 0;
    
    // タッチイベント
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = onTouchBegan();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    
    return true;
}

std::function<bool(cocos2d::Touch*, cocos2d::Event*)> GamePlayScene::onTouchBegan() {
    return [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        //delete unnecessary sprites
        if (!_isGamePlay) {
            Node* explanation = this->getChildByTag(static_cast<int>(kTag::kExplanation));
            Node* getReady = this->getChildByTag(static_cast<int>(kTag::kGetReady));
            
            explanation->removeFromParentAndCleanup(true);
            getReady->removeFromParentAndCleanup(true);
            
            CCLOG("haha");
            // get bird sprite
            BirdSprite* birdSprite = (BirdSprite*)this->getChildByTag(static_cast<int>(kTag::kStartBird));
            birdSprite->setIsGameStart(true);
            _isGamePlay = true;
            _isDead = false;
            flyUpBird();
            return true;
        } else if (!_isDead) {
            flyUpBird();
            return false;
        } else {
            return false;
        }
    };
}

void GamePlayScene::flyUpBird() {
    // get bird sprite
    BirdSprite* birdSprite = (BirdSprite*)this->getChildByTag(static_cast<int>(kTag::kStartBird));
    
}

void GamePlayScene::update(float delta) {
    // if first ground sprite is out of screen, then change the position to right side of the second sprite.
    // and insert at the end of vector
    auto sprite = _groundVector.at(0);
    float maxX = sprite->getBoundingBox().getMaxX();
    if (maxX <= 0) {
        float maxX1 = _groundVector.at(1)->getBoundingBox().getMaxX();
        float groundLength = sprite->getBoundingBox().getMaxX() - sprite->getBoundingBox().getMinX();
        sprite->setPosition(Vec2(maxX1 + groundLength / 2, sprite->getPositionY()));
        
        _groundVector.erase(0);
        _groundVector.pushBack(sprite);
    }
    
    // is game playing
    if (_isGamePlay) {
        // check collision with ground.
        if (checkCollisionWithGround()) {
            //dead
            _isGamePlay = false;
            BirdSprite* birdSprite = (BirdSprite*)this->getChildByTag(static_cast<int>(kTag::kStartBird));
            birdSprite->setIsGameStart(false);
            CCLOG("dead");
            _isDead = true;
        }
    }
}

bool GamePlayScene::checkCollisionWithGround() {
    // get bird sprite
    BirdSprite* birdSprite = (BirdSprite*)this->getChildByTag(static_cast<int>(kTag::kStartBird));
    float minY = birdSprite->getBoundingBox().getMinY();
    // compute ground top y-coordinate.
    float maxY = _groundVector.at(0)->getBoundingBox().getMaxY();
    if (minY <= maxY) {
        return true;
    } else {
        return false;
    }
}

void GamePlayScene::constructBackGround() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
    
    // set background
    Sprite* backgroundSprite = Sprite::create(BACKGROUND_FILENAME);
    backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backgroundSprite, static_cast<int>(kZOrder::kBackground), static_cast<int>(kTag::kBackground));
    
    // set ground sprites
    GroundSprite* backgroundGoundSprite1 = GroundSprite::createGround();
    backgroundGoundSprite1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 10));
    this->addChild(backgroundGoundSprite1, static_cast<int>(kZOrder::kBackground), static_cast<int>(kTag::kBackgroundGround));
    _groundVector.pushBack(backgroundGoundSprite1);
    
    float rightEdgeX = backgroundGoundSprite1->getBoundingBox().getMaxX();  // right end of first ground sprite
    
    GroundSprite* backgroundGoundSprite2 = GroundSprite::createGround();
    backgroundGoundSprite2->setPosition(Vec2(rightEdgeX + visibleSize.width / 2, visibleSize.height / 10));
    this->addChild(backgroundGoundSprite2, static_cast<int>(kZOrder::kBackground), static_cast<int>(kTag::kBackgroundGround));
    _groundVector.pushBack(backgroundGoundSprite2);
    
    // add bird
    BirdSprite* birdSprite = BirdSprite::createBird();
    birdSprite->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 30));
    this->addChild(birdSprite, static_cast<int>(kZOrder::kStartBird), static_cast<int>(kTag::kStartBird));
    birdSprite->animateBirdInStartScene();
    
    // add GET Ready text
    Sprite* getReady = Sprite::create(GET_READY_TEXT_FILENAME);
    float logoHeight = getReady->getBoundingBox().getMaxY() - getReady->getBoundingBox().getMinY();
    getReady->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + logoHeight / 2 + 130));
    getReady->setTag(static_cast<int>(kTag::kGetReady));
    this->addChild(getReady);
    
    // add explanation sprite
    Sprite* explanation = Sprite::create(EXPLANATION_FILENAME);
    explanation->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    explanation->setTag(static_cast<int>(kTag::kExplanation));
    this->addChild(explanation);
}
