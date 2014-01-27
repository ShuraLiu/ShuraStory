//
//  PlayLayer.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-22.
//
//

#include "PlayLayer.h"
#include "GameLogic.h"

PlayLayer::PlayLayer()
: pListrener_(0)
, pLogic_(0)
{
    
}

PlayLayer::~PlayLayer()
{
    CC_SAFE_RELEASE_NULL(pListrener_);
}

void PlayLayer::onEnter()
{
    Layer::onEnter();
    pListrener_ = EventListenerTouchOneByOne::create();
    CC_SAFE_RETAIN(pListrener_);
    pListrener_->setSwallowTouches(false);
    pListrener_->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
    pListrener_->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchMoved, this);
    pListrener_->onTouchEnded = CC_CALLBACK_2(PlayLayer::onTouchEnded, this);
    pListrener_->onTouchCancelled = CC_CALLBACK_2(PlayLayer::onTouchCancelled, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListrener_, this);
}

void PlayLayer::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(pListrener_);
    CC_SAFE_RELEASE_NULL(pListrener_);
}

bool PlayLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    pLogic_->onTouchBegan(this, touch, unused_event);
    return true;
}

void PlayLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    pLogic_->onTouchMoved(this, touch, unused_event);
}

void PlayLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    pLogic_->onTouchEnded(this, touch, unused_event);
}

void PlayLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{
    pLogic_->onTouchCancelled(this, touch, unused_event);
}