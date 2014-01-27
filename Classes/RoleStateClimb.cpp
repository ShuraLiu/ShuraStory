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
#include "config.h"

USING_NS_CC;

RoleStateClimb::RoleStateClimb(Role* pRole)
: pRole_(pRole)
{
    init();
}

RoleStateClimb::~RoleStateClimb()
{
    
}

void RoleStateClimb::enter()
{
    pRole_->runAction(Role::ACTION_MOVE);
//    pRole_->getRoleSprite()->runAction(pRole_->getActions().at(Role::ACTION_MOVE));
}

void RoleStateClimb::exit()
{
    //    pRole_->getRoleSprite()->stopAction(pRole_->getActions().at(Role::ACTION_MOVE));
}

void RoleStateClimb::init()
{
    
}

void RoleStateClimb::update(float delta)
{
    
}