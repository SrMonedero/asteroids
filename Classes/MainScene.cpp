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
    auto rotation = shipSprite->getRotation();
    rotation += 25*delta;
    shipSprite->setRotation(rotation);
    /*auto position = shipSprite->getPosition();
    position.x -= 250 * delta;
    if (position.x  < 0 - (shipSprite->getBoundingBox().size.width / 2))
        position.x = this->getBoundingBox().getMaxX() + shipSprite->getBoundingBox().size.width/2;
    shipSprite->setPosition(position);*/
}
