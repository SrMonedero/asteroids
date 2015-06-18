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
    
    auto listener1 = EventListenerTouchAllAtOnce::create();
    
    listener1->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
    listener1->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    this->scheduleUpdate();
    return true;
}

void MainScene::update(float delta){
    if (touchingLeft && touchingRight) {
        auto position = shipSprite->getPosition();
        position.x -= translationSpeed * delta;
        if (position.x  < 0 - (shipSprite->getBoundingBox().size.width / 2))
            position.x = this->getBoundingBox().getMaxX() + shipSprite->getBoundingBox().size.width/2;
        shipSprite->setPosition(position);
    } else if (touchingLeft) {
        auto rotation = shipSprite->getRotation();
        rotation += -rotationSpeed*delta;
        shipSprite->setRotation(rotation);
    } else if (touchingRight) {
        auto rotation = shipSprite->getRotation();
        rotation += rotationSpeed*delta;
        shipSprite->setRotation(rotation);
    }
}

void MainScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
    for (int i = 0; i < touches.size(); i++) {
        cocos2d::log("You touched %f, %f", touches[i]->getLocationInView().x, touches[i]->getLocationInView().y);
        /*if (touches[0]->getLocationInView().x < visibleSize.width/2) {
            touchingLeft = true;
        } else {
            touchingRight = true;
         }*/
    }
}

void MainScene::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {

}

/*void MainScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, <#cocos2d::Event *event#>)
{
    cocos2d::log("You touched %f, %f", touch->getLocationInView().x, touch->getLocationInView().y);
    if (touch->getLocationInView().x < visibleSize.width/2) {
        touchingLeft = true;
    } else {
        touchingRight = true;
    }
}*/

/*void MainScene::onTouchesEnded(<#const std::vector<cocos2d::Touch *> &touches#>, <#cocos2d::Event *event#>)(cocos2d::Touch* touch, cocos2d::Event* event)
{
    touchingRight = false;
    touchingLeft = false;
}*/
