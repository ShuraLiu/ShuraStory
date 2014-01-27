//
//  AIStateInitial.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#include "AIStateInitial.h"
#include "AI.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

AIStateInitial::AIStateInitial(AI* pAI)
: pAI_(pAI)
{

}

AIStateInitial::~AIStateInitial()
{
    
}

void AIStateInitial::enter()
{
    pAI_->getAISprite()->runAction(pAI_->getActions().at(AI::ACTION_IDLE));
    pAI_->setAIStateCurrent(this);
}

void AIStateInitial::exit()
{
    
}
