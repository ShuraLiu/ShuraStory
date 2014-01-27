//
//  RoleStateAttack.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#include "RoleStateAttack.h"
#include "Role.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

RoleStateAttack::RoleStateAttack(Role* pRole)
: pRole_(pRole)
{

}

RoleStateAttack::~RoleStateAttack()
{
    
}

void RoleStateAttack::enter()
{
    SimpleAudioEngine::getInstance()->playEffect("effect_role_attack.mp3");
    pRole_->runAction(Role::ACTION_ATTACK);
}

void RoleStateAttack::exit()
{
    
}