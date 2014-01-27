//
//  BossStateUnbeatable.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#include "BossStateUnbeatable.h"
#include "Boss.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

BossStateUnbeatable::BossStateUnbeatable(Boss* pBoss)
: pBoss_(pBoss)
{
    
}

BossStateUnbeatable::~BossStateUnbeatable()
{
    
}

void BossStateUnbeatable::enter()
{
    pBoss_->getBossSprite()->runAction(pBoss_->getActions().at(Boss::ACTION_NOT_BEAT));
    pBoss_->setBossStateCurrent(this);
}

void BossStateUnbeatable::exit()
{
    
}