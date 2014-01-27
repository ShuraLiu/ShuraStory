//
//  RoleStatePreClimb.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#include "RoleStatePreClimb.h"
#include "Role.h"
#include "cocos2d.h"

USING_NS_CC;

RoleStatePreClimb::RoleStatePreClimb(Role* pRole)
: pRole_(pRole)
{

}

RoleStatePreClimb::~RoleStatePreClimb()
{
    
}

void RoleStatePreClimb::enter()
{
    pRole_->runAction(Role::ACTION_MOVE);
}

void RoleStatePreClimb::exit()
{
    
}