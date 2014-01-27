//
//  BossStateMove.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#include "BossStateMove.h"
#include "Boss.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

BossStateMove::BossStateMove(Boss* pBoss)
: pBoss_(pBoss)
{

}

BossStateMove::~BossStateMove()
{
    
}

void BossStateMove::enter()
{
    pBoss_->getBossStateCurrent()->exit();
    pBoss_->setCurrentMoveDistance(0);
    pBoss_->getBossSprite()->runAction(pBoss_->getActions().at(Boss::ACTION_MOVE));
    pBoss_->setBossStateCurrent(this);
}

void BossStateMove::exit()
{
    
}
