//
//  RoleStateClimb.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#include "RoleStateClimb.h"
#include "Role.h"
#include "cocos2d.h"

USING_NS_CC;

RoleStateClimb::RoleStateClimb(Role* pRole)
: pRole_(pRole)
{

}

RoleStateClimb::~RoleStateClimb()
{
    
}

void RoleStateClimb::enter()
{
    pRole_->runAction(Role::ACTION_MOVE);
}

void RoleStateClimb::exit()
{
}
