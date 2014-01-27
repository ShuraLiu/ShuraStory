//
//  RoleStateMove.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-22.
//
//

#include "RoleStateMove.h"
#include "Role.h"
#include "cocos2d.h"
#include "config.h"

USING_NS_CC;

RoleStateMove::RoleStateMove(Role* pRole)
: pRole_(pRole)
{
    init();
}

RoleStateMove::~RoleStateMove()
{

}

void RoleStateMove::enter()
{
    pRole_->runAction(Role::ACTION_MOVE);
//    pRole_->getRoleSprite()->runAction(pRole_->getActions().at(Role::ACTION_MOVE));
}

void RoleStateMove::exit()
{

}

void RoleStateMove::init()
{
    
}

void RoleStateMove::update(float delta)
{

}