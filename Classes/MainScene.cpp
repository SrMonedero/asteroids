#include "MainScene.h"
#include <cmath>

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::createWithPhysics();
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
    
    auto physicsBody = PhysicsBody::createBox(Size(shipSprite->getBoundingBox().size.width, shipSprite->getBoundingBox().size.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(true);
    physicsBody->setGravityEnable(false);
    
    shipSprite->setPhysicsBody(physicsBody);
    
    auto listener1 = EventListenerTouchAllAtOnce::create();
    
    listener1->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
    listener1->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    this->scheduleUpdate();
    return true;
}

void MainScene::update(float delta){
    
    //BRAKE SHIP
    auto impulse = shipSprite->getPhysicsBody()->getVelocity();
    shipSprite->getPhysicsBody()->applyImpulse(-1.5*impulse);
    auto position = shipSprite->getPosition();
    
    if (touchingLeft && touchingRight) {
        //IMPULSE SHIP
        auto rads = CC_DEGREES_TO_RADIANS(shipSprite->getRotation());
        shipSprite->getPhysicsBody()->applyImpulse(Vec2( sin(rads) * translationSpeed , cos(rads) * translationSpeed));
    } else if (touchingLeft) {
        auto rotation = shipSprite->getRotation();
        rotation += -rotationSpeed*delta;
        shipSprite->setRotation(rotation);
    } else if (touchingRight) {
        auto rotation = shipSprite->getRotation();
        rotation += rotationSpeed*delta;
        shipSprite->setRotation(rotation);
    }
    //DETECT END OF SCREEN
    if (position.x  < 0)
        position.x = this->getBoundingBox().getMaxX();
    
    if (position.y  < 0)
        position.y = this->getBoundingBox().getMaxY();
    
    if (position.x  > this->getBoundingBox().getMaxX())
        position.x = 0;
    
    if (position.y  > this->getBoundingBox().getMaxY())
        position.y = 0;
    
    shipSprite->setPosition(position);
}

void MainScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
    for (int i = 0; i < touches.size(); i++) {
        cocos2d::log("You touched %f, %f", touches[i]->getLocationInView().x, touches[i]->getLocationInView().y);
        if (touches[i]->getLocationInView().x < visibleSize.width/2) {
            touchingLeft = true;
        } else {
            touchingRight = true;
         }
    }
}

void MainScene::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
    touchingRight = false;
    touchingLeft = false;
}
