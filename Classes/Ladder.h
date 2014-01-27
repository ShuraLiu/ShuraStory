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
    Ladder(unsigned int tag);
    virtual ~Ladder();
    virtual void addToLayer(cocos2d::Layer* layer);
    
public:
    void setPosition(const cocos2d::Point pos);
    float getMidX()
    {
        return pSpriteLadder_->getPositionX() + pSpriteLadder_->getContentSize().width / 2;
    }
    void init();
    
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
    
    unsigned int getTag() const
    {
        return tag_;
    }
    
    cocos2d::Sprite* getSpriteLadder() const
    {
        return pSpriteLadder_;
    }
    
private:
    void menuCallback(cocos2d::Object* pSender);
    
private:
    cocos2d::Sprite* pSpriteLadder_;
    cocos2d::Rect bodyRect_;
    cocos2d::Rect collisionRectDown_;
    cocos2d::Rect collisionRectUp_;
    bool collisioned_;
    cocos2d::Menu* pMenu_;
    unsigned int tag_;
};

#endif /* defined(__mygame__Ladder__) */
