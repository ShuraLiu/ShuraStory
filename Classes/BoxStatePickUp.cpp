//
//  BoxStatePickUp.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#include "BoxStatePickUp.h"
#include "Box.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

BoxStatePickUp::BoxStatePickUp(Box* pBox)
: pBox_(pBox)
{
    
}

BoxStatePickUp::~BoxStatePickUp()
{
    
}

void BoxStatePickUp::enter()
{
    pBox_->getBoxStateCurrent()->exit();
    pBox_->setBoxStateCurrent(this);
}

void BoxStatePickUp::exit()
{
    pBox_->getMenuItems()->removeFromParent();
}