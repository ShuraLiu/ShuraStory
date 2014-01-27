//
//  Ladder.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-22.
//
//

#include "Ladder.h"
#include "GameContext.h"
#include "config.h"

USING_NS_CC;

Ladder::Ladder(const char* fileName, const cocos2d::Point& position)
: collisioned_(false)
, collisionRectUp_(Rect::ZERO)
, collisionRectDown_(Rect::ZERO)
, bodyRect_(Rect::ZERO)
, pSpriteLadder_(0)
{
    init(fileName, position);
}

Ladder::~Ladder()
{
    CC_SAFE_RELEASE_NULL(pSpriteLadder_);
    CC_SAFE_RELEASE_NULL(pMenuDown_);
    CC_SAFE_RELEASE_NULL(pMenuUp_);
}

void Ladder::init(const char* fileName, const cocos2d::Point& position)
{
    pSpriteLadder_ = Sprite::createWithSpriteFrameName(fileName);
    pSpriteLadder_->setAnchorPoint(Point::ZERO);
    pSpriteLadder_->setPosition(position);
    CC_SAFE_RETAIN(pSpriteLadder_);
    collisionRectDown_ = Rect(-32, 0, 128, 50);
    collisionRectUp_ = Rect(-32, 192, 128, 50);
    
    Sprite* normalSprite = Sprite::createWithSpriteFrameName("button_ladder_normal_0.png");
    Sprite* selectedSprite = Sprite::createWithSpriteFrameName("button_ladder_normal_0.png");
    MenuItemSprite* item = MenuItemSprite::create(normalSprite, selectedSprite, CC_CALLBACK_1(Ladder::onMenuUp, this));
    item->setAnchorPoint(Point(0.5, 0.5));
    item->setPosition(Point::ZERO);
    
    pMenuUp_ = Menu::create(item, NULL);
    pMenuUp_->ignoreAnchorPointForPosition(false);
    pMenuUp_->setAnchorPoint(Point::ZERO);
    pMenuUp_->setPosition(Point(pSpriteLadder_->getPositionX() + pSpriteLadder_->getContentSize().width / 2, pSpriteLadder_->getPositionY() + normalSprite->getContentSize().height / 2));
    CC_SAFE_RETAIN(pMenuUp_);
    
    normalSprite = Sprite::createWithSpriteFrameName("button_ladder_normal_1.png");
    selectedSprite = Sprite::createWithSpriteFrameName("button_ladder_normal_1.png");
    item = MenuItemSprite::create(normalSprite, selectedSprite, CC_CALLBACK_1(Ladder::onMenuDown, this));
    item->setAnchorPoint(Point(0.5, 0.5));
    item->setPosition(Point::ZERO);
    
    pMenuDown_ = Menu::create(item, NULL);
    pMenuDown_->ignoreAnchorPointForPosition(false);
    pMenuDown_->setAnchorPoint(Point::ZERO);
    pMenuDown_->setPosition(Point(pSpriteLadder_->getPositionX() + pSpriteLadder_->getContentSize().width / 2, pSpriteLadder_->getPositionY() + pSpriteLadder_->getContentSize().height + normalSprite->getContentSize().height / 2));
    CC_SAFE_RETAIN(pMenuDown_);
}

void Ladder::onMenuUp(cocos2d::Object *obj)
{
    pMenuUp_->removeFromParent();
    GameContext& context = GameContext::getInstance();
    context.getRole()->climb(this, true);
}

void Ladder::onMenuDown(cocos2d::Object *obj)
{
    pMenuDown_->removeFromParent();
    GameContext& context = GameContext::getInstance();
    context.getRole()->climb(this, false);
}

void Ladder::addToLayer(cocos2d::Layer *layer)
{
    layer->addChild(pSpriteLadder_, ROLE_Z_ORDER - 1);
}
