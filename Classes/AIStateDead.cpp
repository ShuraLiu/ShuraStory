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
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

AIStateDead::AIStateDead(AI* pAI)
: pAI_(pAI)
{

}

AIStateDead::~AIStateDead()
{
    
}

void AIStateDead::enter()
{
    SimpleAudioEngine::getInstance()->playEffect("effect_ai_dead.mp3");
    pAI_->getAIStateCurrent()->exit();
    pAI_->getActorSprite()->runAction(pAI_->getActions().at(AI::ACTION_DEAD));
    pAI_->setAIStateCurrent(this);
}

void AIStateDead::exit()
{
    
}
