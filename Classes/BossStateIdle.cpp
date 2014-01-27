//
//  BossStateIdle.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#include "BossStateIdle.h"
#include "Boss.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

BossStateIdle::BossStateIdle(Boss* pBoss)
: pBoss_(pBoss)
{

}

BossStateIdle::~BossStateIdle()
{
    
}

void BossStateIdle::enter()
{
    if(pBoss_->getBossStateCurrent())
    {
        pBoss_->getBossStateCurrent()->exit();
    }
    pBoss_->setCurrentIdleDuration(0);
    pBoss_->getBossSprite()->runAction(pBoss_->getActions().at(Boss::ACTION_IDLE));
    pBoss_->setBossStateCurrent(this);
}

void BossStateIdle::exit()
{
    
}