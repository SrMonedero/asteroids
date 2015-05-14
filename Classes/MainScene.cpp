#include "MainScene.h"
#include <cmath>

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    touchingLeft = false;
    touchingRight = false;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    shipSprite = Sprite::create("ship.png");
    shipSprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    shipSprite->setScale(0.15, 0.15);
    this->addChild(shipSprite);
    
    auto listener1 = EventListenerTouchAllAtOnce::create();
    
    listener1->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
    listener1->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    this->scheduleUpdate();
    return true;
}

void MainScene::update(float delta){
    if (touchingLeft) {
        auto rotation = shipSprite->getRotation();
        rotation += -speed*delta;
        shipSprite->setRotation(rotation);
    } else if (touchingRight) {
        auto rotation = shipSprite->getRotation();
        rotation += speed*delta;
        shipSprite->setRotation(rotation);
    }
    /*auto position = shipSprite->getPosition();
    position.x -= 250 * delta;
    if (position.x  < 0 - (shipSprite->getBoundingBox().size.width / 2))
        position.x = this->getBoundingBox().getMaxX() + shipSprite->getBoundingBox().size.width/2;
    shipSprite->setPosition(position);*/
}

void MainScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
    for (int i = 0; i < MIN(2, touches.size()); i++) {
    }
    /*if (touch->getLocationInView().x < visibleSize.width/2) {
        touchingLeft = true;
        touchingRight = false;
    } else {
        touchingLeft = false;
        touchingRight = true;
    }*/
}

void MainScene::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
    touchingRight = false;
    touchingLeft = false;
}
