//
//  AIStateAttack.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#include "AIStateAttack.h"
#include "AI.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

AIStateAttack::AIStateAttack(AI* pAI)
: pAI_(pAI)
{

}

AIStateAttack::~AIStateAttack()
{
    
}

void AIStateAttack::enter()
{
    pAI_->getAIStateCurrent()->exit();
    pAI_->getAISprite()->runAction(pAI_->getActions().at(AI::ACTION_ATTACK));
    pAI_->setAIStateCurrent(this);
}

void AIStateAttack::exit()
{
    
}