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
#include "config.h"

USING_NS_CC;

RoleStatePreClimb::RoleStatePreClimb(Role* pRole)
: pRole_(pRole)
{
    init();
}

RoleStatePreClimb::~RoleStatePreClimb()
{
    
}

void RoleStatePreClimb::enter()
{
    pRole_->runAction(Role::ACTION_MOVE);
//    pRole_->getRoleSprite()->runAction(pRole_->getActions().at(Role::ACTION_MOVE));
}

void RoleStatePreClimb::exit()
{
    //    pRole_->getRoleSprite()->stopAction(pRole_->getActions().at(Role::ACTION_MOVE));
}

void RoleStatePreClimb::init()
{
    
}

void RoleStatePreClimb::update(float delta)
{

}