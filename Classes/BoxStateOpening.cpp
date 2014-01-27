//
//  BoxStateOpening.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#include "BoxStateOpening.h"
#include "Box.h"
#include "cocos2d.h"
#include "GameContext.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

BoxStateOpening::BoxStateOpening(Box* pBox)
: pBox_(pBox)
{
    
}

BoxStateOpening::~BoxStateOpening()
{
    
}

void BoxStateOpening::enter()
{
    SimpleAudioEngine::getInstance()->playEffect("effect_open_box.mp3");
    pBox_->getBoxStateCurrent()->exit();
    pBox_->open();
    pBox_->setBoxStateCurrent(this);
}

void BoxStateOpening::exit()
{
    
}