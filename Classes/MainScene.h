#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    
    void update(float) override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
    
private:
    cocos2d::Sprite* shipSprite;
    cocos2d::Sprite* bulletSprite;
    bool touchingLeft;
    bool touchingRight;
    cocos2d::Size visibleSize;
    const int rotationSpeed = 150;
    const int translationSpeed = 800;
    void onTouchesBegan(const std::vector<cocos2d::Touch* > &touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch* > &touches, cocos2d::Event* event);
    const int speed = 25;
    int firstTouchID;
    int secondTouchID;
};

#endif // __MAIN_SCENE_H__
