//
//  Box.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#ifndef __ShuraStory__Box__
#define __ShuraStory__Box__

#include "SceneObject.h"
#include "cocos2d.h"

class BaseState;

enum BOX_STATE
{
    BOX_STATE_NONE,
    BOX_STATE_IDLE,
    BOX_STATE_READY_TO_OPEN,
    BOX_STATE_OPENING,
    BOX_STATE_PICK_UP,
    BOX_STATE_BOMB,
};

class Box : public SceneObject
{
public:
    Box(const cocos2d::Point& position, bool bomb, bool pass, bool coin);
    virtual ~Box();
    virtual void update(float delta);
    
public:
    void init();
    virtual void addToLayer(cocos2d::Layer* layer);
    void idle();
    void readyToOpen();
    void dealCollision();
    void open();
    
public:
    cocos2d::Sprite* getBoxSprite()
    {
        return pSpriteBox_;
    }
    
    cocos2d::Menu* getMenuOpen()
    {
        return pMenuOpen_;
    }
    
    cocos2d::Menu* getMenuItems()
    {
        return pMenuItems_;
    }
    
    BOX_STATE getCurrentState()
    {
        return mState_;
    }
    
private:
    void initMenuOpen();
    void initMenuItems();
    bool changeState(BOX_STATE state);
    void onMenuOpen(cocos2d::Object* obj);
    void onMenuBomb(cocos2d::Object* obj);
    void onMenuPass(cocos2d::Object* obj);

    
    CC_SYNTHESIZE(cocos2d::Rect, collisionRect_, CollisionRect);
    CC_SYNTHESIZE(cocos2d::Point, position_, Position);
    CC_SYNTHESIZE(bool, bomb_, Bomb);
    CC_SYNTHESIZE(bool, pass_, Pass);
    CC_SYNTHESIZE(bool, coin_, Coin);
    
private:
    BaseState* pBoxStateIdle_;
    BaseState* pBoxStateReadyToOpen_;
    BaseState* pBoxStateOpening_;
    BaseState* pBoxStatePickUp_;
    BaseState* pBoxStateBomb_;
    CC_SYNTHESIZE(BaseState*, pBoxStateCurrent_, BoxStateCurrent);
    
    BOX_STATE mState_;
    
    cocos2d::Sprite* pSpriteBox_;
    cocos2d::Menu* pMenuItems_;
    cocos2d::Menu* pMenuOpen_;
};

#endif /* defined(__ShuraStory__Box__) */
