//
//  AIStateMove.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#include "AIStateMove.h"
#include "AI.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

AIStateMove::AIStateMove(AI* pAI)
: pAI_(pAI)
{

}

AIStateMove::~AIStateMove()
{
    
}

void AIStateMove::enter()
{
    pAI_->getAIStateCurrent()->exit();
    pAI_->setCurrentMoveDistance(0);
    pAI_->getAISprite()->runAction(pAI_->getActions().at(AI::ACTION_MOVE));
    pAI_->setAIStateCurrent(this);
}

void AIStateMove::exit()
{
    
}
