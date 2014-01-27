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

Ladder::Ladder(unsigned int tag)
: collisioned_(false)
, collisionRectUp_(Rect::ZERO)
, collisionRectDown_(Rect::ZERO)
, bodyRect_(Rect::ZERO)
, pSpriteLadder_(0)
, tag_(tag)
{
    init();
}

Ladder::~Ladder()
{
    CC_SAFE_RELEASE_NULL(pSpriteLadder_);
}

void Ladder::init()
{
    pSpriteLadder_ = Sprite::createWithSpriteFrameName("ladder_0.png");
    pSpriteLadder_->setAnchorPoint(Point::ZERO);
    pSpriteLadder_->setPosition(Point::ZERO);
    CC_SAFE_RETAIN(pSpriteLadder_);
    collisionRectDown_ = Rect(0, 0, 75, 50);
    collisionRectUp_ = Rect(0, 192, 75, 50);
}

void Ladder::setPosition(const cocos2d::Point pos)
{
    pSpriteLadder_->setPosition(pos);
}

void Ladder::addToLayer(cocos2d::Layer *layer)
{
    layer->addChild(pSpriteLadder_, ROLE_Z_ORDER - 1);
}
