//
//  AIStateRevival.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#include "AIStateRevival.h"
#include "AI.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

AIStateRevival::AIStateRevival(AI* pAI)
: pAI_(pAI)
{
    
}

AIStateRevival::~AIStateRevival()
{
    
}

void AIStateRevival::enter()
{
    pAI_->getAISprite()->setVisible(false);
    pAI_->setCurrentRevivalDuration(0);
    pAI_->setAIStateCurrent(this);
}

void AIStateRevival::exit()
{
    pAI_->reset();
    pAI_->getAISprite()->setVisible(true);
}