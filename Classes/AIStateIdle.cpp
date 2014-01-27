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
    init();
}

AIStateIdle::~AIStateIdle()
{
    
}

void AIStateIdle::enter()
{
    pAI_->getAISprite()->runAction(pAI_->getActions().at(AI::ACTION_IDLE));
}

void AIStateIdle::exit()
{
    
}

void AIStateIdle::init()
{
    
}

void AIStateIdle::update(float delta)
{
    
}