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
#include "config.h"

USING_NS_CC;

RoleStateAttack::RoleStateAttack(Role* pRole)
: pRole_(pRole)
{
    init();
}

RoleStateAttack::~RoleStateAttack()
{
    
}

void RoleStateAttack::enter()
{
    pRole_->runAction(Role::ACTION_ATTACK);
//    pRole_->getRoleSprite()->runAction(pRole_->getActions().at(Role::ACTION_ATTACK));
}

void RoleStateAttack::exit()
{
    
}

void RoleStateAttack::init()
{
    
}

void RoleStateAttack::update(float delta)
{
    
}