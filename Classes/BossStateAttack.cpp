//
//  BossStateAttack.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#include "BossStateAttack.h"
#include "Boss.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

BossStateAttack::BossStateAttack(Boss* pBoss)
: pBoss_(pBoss)
{

}

BossStateAttack::~BossStateAttack()
{
    
}

void BossStateAttack::enter()
{
    pBoss_->getBossStateCurrent()->exit();
    pBoss_->getBossSprite()->runAction(pBoss_->getActions().at(Boss::ACTION_ATTACK));
    pBoss_->setBossStateCurrent(this);
}

void BossStateAttack::exit()
{
    
}