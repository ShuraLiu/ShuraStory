//
//  BossStateDead.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#include "BossStateDead.h"
#include "Boss.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

BossStateDead::BossStateDead(Boss* pBoss)
: pBoss_(pBoss)
{

}

BossStateDead::~BossStateDead()
{
    
}

void BossStateDead::enter()
{
    pBoss_->getBossStateCurrent()->exit();
    pBoss_->getBossSprite()->runAction(pBoss_->getActions().at(Boss::ACTION_DEAD));
    pBoss_->setBossStateCurrent(this);
}

void BossStateDead::exit()
{
    
}
