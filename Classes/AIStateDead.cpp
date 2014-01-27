//
//  AIStateDead.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#include "AIStateDead.h"
#include "AI.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

AIStateDead::AIStateDead(AI* pAI)
: pAI_(pAI)
{
    init();
}

AIStateDead::~AIStateDead()
{
    
}

void AIStateDead::enter()
{
    pAI_->getAISprite()->runAction(pAI_->getActions().at(AI::ACTION_DEAD));
}

void AIStateDead::exit()
{
    
}

void AIStateDead::init()
{
    
}

void AIStateDead::update(float delta)
{
    
}