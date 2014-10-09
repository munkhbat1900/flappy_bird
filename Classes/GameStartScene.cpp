#include "GameStartScene.h"
#include "Consts.h"

USING_NS_CC;

Scene* GameStartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameStartScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameStartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    constructBackGround();
    
    scheduleUpdate();
    
    return true;
}

void GameStartScene::update(float delta) {
    // move ground
    
}

void GameStartScene::constructBackGround() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
    
    // set background
    Sprite* backgroundSprite = Sprite::create(BACKGROUND_FILENAME);
    backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backgroundSprite, static_cast<int>(kZOrder::kBackground), static_cast<int>(kTag::kBackground));
    
    // set ground
    Sprite* backgroundGoundSprite = Sprite::create(BACKGROUND_GROUND_FILENAME);
    backgroundGoundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 10));
    this->addChild(backgroundGoundSprite, static_cast<int>(kZOrder::kBackground), static_cast<int>(kTag::kBackgroundGround));
}
