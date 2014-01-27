//
//  Ladder.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-22.
//
//

#ifndef __mygame__Ladder__
#define __mygame__Ladder__

#include "SceneObject.h"
#include "cocos2d.h"

class Ladder : public SceneObject
{
public:
    Ladder(const char* fileName, const cocos2d::Point& position);
    virtual ~Ladder();
    virtual void addToLayer(cocos2d::Layer* layer);
    
public:
    float getMidX()
    {
        return pSpriteLadder_->getPositionX() + pSpriteLadder_->getContentSize().width / 2;
    }
    void init(const char* fileName, const cocos2d::Point& position);
    
public:
    void onCollision()
    {
        collisioned_ = true;
//        pMenu_->setVisible(true);
    }
    
    void noCollision()
    {
        collisioned_ = false;
//        pMenu_->setVisible(false);
    }
    
    bool isCollisioned() const
    {
        return collisioned_;
    }
    
    cocos2d::Rect getCollsionRectDown()
    {
        return cocos2d::Rect(pSpriteLadder_->getPositionX() + collisionRectDown_.origin.x, pSpriteLadder_->getPositionY() + collisionRectDown_.origin.y, collisionRectDown_.size.width, collisionRectDown_.size.height);
    }
    
    cocos2d::Rect getCollsionRectUp()
    {
        return cocos2d::Rect(pSpriteLadder_->getPositionX() + collisionRectUp_.origin.x, pSpriteLadder_->getPositionY() + collisionRectUp_.origin.y, collisionRectUp_.size.width, collisionRectUp_.size.height);
    }
    
    cocos2d::Sprite* getSpriteLadder() const
    {
        return pSpriteLadder_;
    }
    
    cocos2d::Menu* getMenuUp()
    {
        return pMenuUp_;
    }
    
    cocos2d::Menu* getMenuDown() 
    {
        return pMenuDown_;
    }
    
private:
    void menuCallback(cocos2d::Object* pSender);
    void onMenuUp(cocos2d::Object* obj);
    void onMenuDown(cocos2d::Object* obj);
    
private:
    cocos2d::Sprite* pSpriteLadder_;
    cocos2d::Rect bodyRect_;
    cocos2d::Rect collisionRectDown_;
    cocos2d::Rect collisionRectUp_;
    cocos2d::Menu* pMenuUp_;
    cocos2d::Menu* pMenuDown_;
    bool collisioned_;
};

#endif /* defined(__mygame__Ladder__) */
