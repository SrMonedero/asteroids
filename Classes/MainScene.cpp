#include "MainScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    shipSprite = Sprite::create("ship.png");
    shipSprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    shipSprite->setScale(0.15, 0.15);
    this->addChild(shipSprite);
    
    this->scheduleUpdate();
    return true;
}

void MainScene::update(float delta){
    auto position = shipSprite->getPosition();
    position.x -= 250 * delta;
    if (position.x  < 0 - (shipSprite->getBoundingBox().size.width / 2))
        position.x = this->getBoundingBox().getMaxX() + shipSprite->getBoundingBox().size.width/2;
    shipSprite->setPosition(position);
}
