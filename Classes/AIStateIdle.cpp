//
//  AIStateIdle.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#include "AIStateIdle.h"
#include "AI.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

AIStateIdle::AIStateIdle(AI* pAI)
: pAI_(pAI)
{

}

AIStateIdle::~AIStateIdle()
{
    
}

void AIStateIdle::enter()
{
    pAI_->getAIStateCurrent()->exit();
    pAI_->setCurrentIdleDuration(0);
    pAI_->getActorSprite()->runAction(pAI_->getActions().at(AI::ACTION_IDLE));
    pAI_->setAIStateCurrent(this);
}

void AIStateIdle::exit()
{
    
}