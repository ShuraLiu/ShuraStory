//
//  BoxStateIdle.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#include "BoxStateIdle.h"
#include "Box.h"
#include "cocos2d.h"
#include "GameContext.h"

USING_NS_CC;

BoxStateIdle::BoxStateIdle(Box* pBox)
: pBox_(pBox)
{
    
}

BoxStateIdle::~BoxStateIdle()
{
    
}

void BoxStateIdle::enter()
{
    if (pBox_->getBoxStateCurrent() != this)
    {
        pBox_->getBoxStateCurrent()->exit();
    }
    pBox_->getBoxSprite()->setSpriteFrame("box_0_idle_0.png");
    pBox_->setBoxStateCurrent(this);
}

void BoxStateIdle::exit()
{
    
}