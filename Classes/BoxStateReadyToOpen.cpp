//
//  BoxStateReadyToOpen.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#include "BoxStateReadyToOpen.h"
#include "Box.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

BoxStateReadyToOpen::BoxStateReadyToOpen(Box* pBox)
: pBox_(pBox)
{
    
}

BoxStateReadyToOpen::~BoxStateReadyToOpen()
{
    
}

void BoxStateReadyToOpen::enter()
{
    pBox_->getBoxStateCurrent()->exit();
    pBox_->setBoxStateCurrent(this);
}

void BoxStateReadyToOpen::exit()
{
    pBox_->getMenuOpen()->removeFromParent();
}