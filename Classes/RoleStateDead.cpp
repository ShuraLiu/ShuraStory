//
//  RoleStateDead.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#include "RoleStateDead.h"
#include "Role.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

RoleStateDead::RoleStateDead(Role* pRole)
: pRole_(pRole)
{
    
}

RoleStateDead::~RoleStateDead()
{
    
}

void RoleStateDead::enter()
{
    SimpleAudioEngine::getInstance()->playEffect("effect_failed.mp3");
    pRole_->runAction(Role::ACTION_DEAD);
    //    pRole_->getRoleSprite()->runAction(pRole_->getActions().at(Role::ACTION_IDLE));
}

void RoleStateDead::exit()
{
    
}