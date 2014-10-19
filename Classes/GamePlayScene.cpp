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
    auto scene = Scene::createWithPhysics();
    
    auto world = scene->getPhysicsWorld();
    
    world->setGravity(Vec2(0, -900));
    //world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
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
    
    // contact listsner.
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GamePlayScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

bool GamePlayScene::onContactBegin( cocos2d::PhysicsContact &contact ) {
    PhysicsBody *body1 = contact.getShapeA()->getBody();
    PhysicsBody *body2 = contact.getShapeB()->getBody();
    
    // it seems like sometimes nodes can't get Nodes.
    if (body1 == nullptr || body2 == nullptr) {
        return true;
    }
    
    auto tag1 = body1->getTag();
    auto tag2 = body2->getTag();
    
    int tagBirdGround = static_cast<int>(PhysicsBodyTag::BIRD) + static_cast<int>(PhysicsBodyTag::GROUND);
    
    if (tag1 + tag2 == tagBirdGround) {
        _isDead = true;
        CCLOG("dead");
    }
    return true;
}

void GamePlayScene::createPipes() {
    for (int i = 0; i < PIPE_COUNT_SHOWN; i++) {
        
    }
}

std::function<bool(cocos2d::Touch*, cocos2d::Event*)> GamePlayScene::onTouchBegan() {
    return [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        //delete unnecessary sprites
        if (!_isGamePlay && !_isDead) {
            Node* explanation = this->getChildByTag(static_cast<int>(kTag::kExplanation));
            Node* getReady = this->getChildByTag(static_cast<int>(kTag::kGetReady));
            
            explanation->removeFromParentAndCleanup(true);
            getReady->removeFromParentAndCleanup(true);
            
            _birdSprite->gameStart();
            _isGamePlay = true;
            _isDead = false;
            
            // set rigid body to sprite
            auto material = PHYSICSBODY_MATERIAL_DEFAULT;
            material.restitution = 0.0f;
            material.friction = 0.0f;
            auto body = PhysicsBody::createBox(_birdSprite->getContentSize(), material);
            body->setContactTestBitmask(BIRD_COLLISION_MASK);
            body->setTag(static_cast<int>(PhysicsBodyTag::BIRD));
            _birdSprite->setPhysicsBody(body);
            
            body->setGravityEnable(false);
            _birdSprite->getPhysicsBody()->setVelocity(Vec2(0, BIRD_FLY_SPEED));
            
            this->scheduleOnce(schedule_selector(GamePlayScene::stopFlying), BIRD_FLY_TIME);
            _birdSprite->swingAnimation();
            return true;
        } else if (!_isDead) {
            _birdSprite->getPhysicsBody()->setGravityEnable(false);
            _birdSprite->getPhysicsBody()->setVelocity(Vec2(0, BIRD_FLY_SPEED));
            this->scheduleOnce(schedule_selector(GamePlayScene::stopFlying), BIRD_FLY_TIME);
            return true;
        } else {
            return false;
        }
    };
}

void GamePlayScene::stopFlying(float delta) {
    _birdSprite->getPhysicsBody()->setGravityEnable(true);
}

void GamePlayScene::rotateBird() {
    float velocity = _birdSprite->getPhysicsBody()->getVelocity().y;
    _birdSprite->setRotation(MIN(MAX(-45, (-velocity*0.1)), 90));
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
    
    if (_isGamePlay) {
        rotateBird();
    }
}

void GamePlayScene::createGround() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // set ground sprites
    GroundSprite* goundSprite1 = GroundSprite::createGround();
    goundSprite1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 10));
    this->addChild(goundSprite1, static_cast<int>(kZOrder::kBackground), static_cast<int>(kTag::kBackgroundGround));
    _groundVector.pushBack(goundSprite1);
    
    // set physics to grounds
    
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.restitution = 0.0f;
    material.friction = 0.0f;
    
    //auto body1 = PhysicsBody::createBox(goundSprite1->getContentSize());
    auto body1 = PhysicsBody::createBox(goundSprite1->getContentSize(), material);
    goundSprite1->setPhysicsBody(body1);
    body1->setGravityEnable(false);
    body1->setContactTestBitmask(OBSTACLE_COLLISION_MASK);
    body1->setContactTestBitmask(true);
    body1->setDynamic(false);
    body1->setTag(static_cast<int>(PhysicsBodyTag::GROUND));
    
    float rightEdgeX = goundSprite1->getBoundingBox().getMaxX();  // right end of first ground sprite
    
    GroundSprite* groundSprite2 = GroundSprite::createGround();
    groundSprite2->setPosition(Vec2(rightEdgeX + visibleSize.width / 2, visibleSize.height / 10));
    this->addChild(groundSprite2, static_cast<int>(kZOrder::kBackground), static_cast<int>(kTag::kBackgroundGround));
    _groundVector.pushBack(groundSprite2);
    
    //auto body2 = PhysicsBody::createBox(groundSprite2->getContentSize());
    auto body2 = PhysicsBody::createBox(groundSprite2->getContentSize(), material);
    groundSprite2->setPhysicsBody(body2);
    body2->setGravityEnable(false);
    body2->setContactTestBitmask(OBSTACLE_COLLISION_MASK);
    body2->setContactTestBitmask(true);
    body2->setDynamic(false);
    body2->setTag(static_cast<int>(PhysicsBodyTag::GROUND));
}

void GamePlayScene::constructBackGround() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
    
    // set background
    Sprite* backgroundSprite = Sprite::create(BACKGROUND_FILENAME);
    backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backgroundSprite, static_cast<int>(kZOrder::kBackground), static_cast<int>(kTag::kBackground));
    
    createGround();
    
    // add bird
    _birdSprite = BirdSprite::createBird();
    _birdSprite->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 30));
    this->addChild(_birdSprite, static_cast<int>(kZOrder::kStartBird), static_cast<int>(kTag::kStartBird));
    _birdSprite->animateBirdInStartScene();
    
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
