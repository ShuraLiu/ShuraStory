//
//  RoleStateVictory.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#include "RoleStateVictory.h"
#include "Role.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

RoleStateVictory::RoleStateVictory(Role* pRole)
: pRole_(pRole)
{
    
}

RoleStateVictory::~RoleStateVictory()
{
    
}

void RoleStateVictory::enter()
{
    SimpleAudioEngine::getInstance()->playEffect("effect_role_victory.mp3");
    pRole_->runAction(Role::ACTION_VICTORY);
}

void RoleStateVictory::exit()
{
    
}