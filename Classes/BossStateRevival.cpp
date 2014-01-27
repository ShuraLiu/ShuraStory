//
//  BossStateRevival.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#include "BossStateRevival.h"
#include "Boss.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

BossStateRevival::BossStateRevival(Boss* pBoss)
: pBoss_(pBoss)
{
    
}

BossStateRevival::~BossStateRevival()
{
    
}

void BossStateRevival::enter()
{
    pBoss_->getBossSprite()->setVisible(false);
    pBoss_->setCurrentRevivalDuration(0);
    pBoss_->setBossStateCurrent(this);
}

void BossStateRevival::exit()
{
    pBoss_->getBossSprite()->setVisible(true);
}