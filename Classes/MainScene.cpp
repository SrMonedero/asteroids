#include "MainScene.h"

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
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    listener1->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    
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

bool MainScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    cocos2d::log("You touched %f, %f", touch->getLocationInView().x, touch->getLocationInView().y);
    if (touch->getLocationInView().x < visibleSize.width/2) {
        touchingLeft = true;
        touchingRight = false;
    } else {
        touchingLeft = false;
        touchingRight = true;
    }
    return true;
}

void MainScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    touchingRight = false;
    touchingLeft = false;
}
