//
//  RoleStateIdle.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#include "RoleStateIdle.h"
#include "Role.h"
#include "cocos2d.h"

USING_NS_CC;

RoleStateIdle::RoleStateIdle(Role* pRole)
: pRole_(pRole)
{

}

RoleStateIdle::~RoleStateIdle()
{
    
}

void RoleStateIdle::enter()
{
    pRole_->runAction(Role::ACTION_IDLE);
    //    pRole_->getRoleSprite()->runAction(pRole_->getActions().at(Role::ACTION_IDLE));
}

void RoleStateIdle::exit()
{
    
}