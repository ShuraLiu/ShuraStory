//
//  Box.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#include "Box.h"
#include "BoxStateIdle.h"
#include "BoxStateReadyToOpen.h"
#include "BoxStateOpening.h"
#include "BoxStatePickUp.h"
#include "BoxStateBomb.h"
#include "config.h"
#include "GameContext.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

static const int BOX_ACTION_OPENING_TAG = 301;
static const int BOX_MENU_BOMB_TAG = 302;

Box::Box(const cocos2d::Point& position, bool bomb, bool pass, bool coin)
: pBoxStateBomb_(new BoxStateBomb(this))
, pBoxStateIdle_(new BoxStateIdle(this))
, pBoxStateReadyToOpen_(new BoxStateReadyToOpen(this))
, pBoxStateOpening_(new BoxStateOpening(this))
, pBoxStatePickUp_(new BoxStatePickUp(this))
, mState_(BOX_STATE_NONE)
, position_(position)
, pBoxStateCurrent_(pBoxStateIdle_)
, pMenuOpen_(0)
, pSpriteBox_(0)
, bomb_(bomb)
, pass_(pass)
, coin_(coin)
{
    init();
}

Box::~Box()
{
    delete pBoxStatePickUp_;
    delete pBoxStateBomb_;
    delete pBoxStateIdle_;
    delete pBoxStateOpening_;
    delete pBoxStateReadyToOpen_;
    CC_SAFE_RELEASE_NULL(pSpriteBox_);
    CC_SAFE_RELEASE_NULL(pMenuOpen_);
    CC_SAFE_RELEASE_NULL(pMenuItems_);
}

void Box::init()
{
    pSpriteBox_ = Sprite::createWithSpriteFrameName("box_0_idle_0.png");
    pSpriteBox_->setAnchorPoint(Point::ZERO);
    pSpriteBox_->setPosition(position_);
    CC_SAFE_RETAIN(pSpriteBox_);
    
    setCollisionRect(Rect(position_.x, position_.y, pSpriteBox_->getContentSize().width, pSpriteBox_->getContentSize().height));
    
    initMenuOpen();
    initMenuItems();
    if (changeState(BOX_STATE_IDLE))
    {
        pBoxStateIdle_->enter();
    }
}

void Box::update(float delta)
{
    switch (mState_) {
        case BOX_STATE_OPENING:
        {
            if (!pSpriteBox_->getActionByTag(BOX_ACTION_OPENING_TAG))
            {
                if (changeState(BOX_STATE_PICK_UP))
                {
                    pBoxStatePickUp_->enter();
                }
            }
        }
            break;
        default:
            break;
    }
}

bool Box::changeState(BOX_STATE state)
{
    pSpriteBox_->stopAllActions();
    mState_ = state;
    return true;
}

void Box::readyToOpen()
{
    if (changeState(BOX_STATE_READY_TO_OPEN))
    {
        pBoxStateReadyToOpen_->enter();
    }
}

void Box::onMenuOpen(cocos2d::Object *obj)
{
    if (changeState(BOX_STATE_OPENING))
    {
        pBoxStateOpening_->enter();
    }
}

void Box::addToLayer(cocos2d::Layer *layer)
{
    layer->addChild(pSpriteBox_, ROLE_Z_ORDER - 1);
}

void Box::dealCollision()
{
    if (mState_ == BOX_STATE_IDLE && changeState(BOX_STATE_READY_TO_OPEN))
    {
        pBoxStateReadyToOpen_->enter();
    }
}

void Box::idle()
{
    if (changeState(BOX_STATE_IDLE))
    {
        pBoxStateIdle_->enter();
    }
}

void Box::open()
{
    Animate* action = Animate::create(AnimationCache::getInstance()->getAnimation("box_0_opening"));
    action->setTag(BOX_ACTION_OPENING_TAG);
    pSpriteBox_->runAction(action);
}

void Box::initMenuOpen()
{
    Sprite* normalSprite = Sprite::createWithSpriteFrameName("button_box_open.png");
    Sprite* selectedSprite = Sprite::createWithSpriteFrameName("button_box_open.png");
    MenuItemSprite* item = MenuItemSprite::create(normalSprite, selectedSprite, CC_CALLBACK_1(Box::onMenuOpen, this));
    item->setAnchorPoint(Point(0.5, 0.5));
    item->setPosition(Point::ZERO);
    
    pMenuOpen_ = Menu::create(item, NULL);
    pMenuOpen_->ignoreAnchorPointForPosition(false);
    pMenuOpen_->setAnchorPoint(Point::ZERO);
    pMenuOpen_->setPosition(Point(pSpriteBox_->getPositionX() + pSpriteBox_->getContentSize().width / 2, pSpriteBox_->getPositionY() + pSpriteBox_->getContentSize().height));
    CC_SAFE_RETAIN(pMenuOpen_);
}

void Box::initMenuItems()
{
    MenuItemSprite* itemBomb = 0;
//    MenuItemSprite* itemPass = 0;
    
//    if (bomb_)
//    {
        Sprite* normalSprite = Sprite::createWithSpriteFrameName("button_bomb_pickup.png");
        Sprite* selectedSprite = Sprite::createWithSpriteFrameName("button_bomb_pickup.png");
        itemBomb = MenuItemSprite::create(normalSprite, selectedSprite, CC_CALLBACK_1(Box::onMenuBomb, this));
        itemBomb->setAnchorPoint(Point::ZERO);
        itemBomb->setPosition(Point::ZERO);
        itemBomb->setTag(BOX_MENU_BOMB_TAG);
//    }
//    if (pass_)
//    {
//        Sprite* normalSprite = Sprite::createWithSpriteFrameName("button_shura_eye_pickup.png");
//        Sprite* selectedSprite = Sprite::createWithSpriteFrameName("button_shura_eye_pickup.png");
//        itemPass = MenuItemSprite::create(normalSprite, selectedSprite, CC_CALLBACK_1(Box::onMenuPass, this));
//        itemPass->setAnchorPoint(Point::ZERO);
//        itemPass->setPosition(Point::ZERO);
//    }
    
//    if (pass_)
//    {
//        pMenuItems_ = Menu::create(itemPass, NULL);
//    }
//    else if (bomb_)
//    {
        pMenuItems_ = Menu::create(itemBomb, NULL);
//    }
    Sprite* temp = Sprite::createWithSpriteFrameName("button_bomb_pickup.png");
    pMenuItems_->setContentSize(Size(temp->getContentSize().width, temp->getContentSize().height));
    pMenuItems_->ignoreAnchorPointForPosition(false);
    pMenuItems_->setAnchorPoint(Point(0.5, 0));
    pMenuItems_->setPosition(Point(pSpriteBox_->getPositionX() + pSpriteBox_->getContentSize().width / 2, pSpriteBox_->getPositionY() + pSpriteBox_->getContentSize().height));
    CC_SAFE_RETAIN(pMenuItems_);
}

void Box::onMenuBomb(cocos2d::Object *obj)
{
    SimpleAudioEngine::getInstance()->playEffect("effect_pickup.mp3");
    GameContext::getInstance().addBomb(1);
    if (changeState(BOX_STATE_BOMB))
    {
        pBoxStateBomb_->enter();
    }
}

void Box::onMenuPass(cocos2d::Object *obj)
{
    GameContext::getInstance().gameVictory();
}
