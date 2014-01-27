//
//  BossStateNotMove.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-26.
//
//

#include "BossStateNotMove.h"
#include "Boss.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

BossStateNotMove::BossStateNotMove(Boss* pBoss)
: pBoss_(pBoss)
{
    
}

BossStateNotMove::~BossStateNotMove()
{
    
}

void BossStateNotMove::enter()
{
    pBoss_->getBossSprite()->runAction(pBoss_->getActions().at(Boss::ACTION_NOT_BEAT));
    pBoss_->setBossStateCurrent(this);
}

void BossStateNotMove::exit()
{
    
}