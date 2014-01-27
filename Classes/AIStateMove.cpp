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
    init();
}

AIStateMove::~AIStateMove()
{
    
}

void AIStateMove::enter()
{
    pAI_->getAISprite()->runAction(pAI_->getActions().at(AI::ACTION_MOVE));
}

void AIStateMove::exit()
{
    
}

void AIStateMove::init()
{
    
}

void AIStateMove::update(float delta)
{
    
}