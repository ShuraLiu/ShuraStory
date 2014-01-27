//
//  BoxStateBomb.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#include "BoxStateBomb.h"
#include "Box.h"
#include "cocos2d.h"
#include "GameContext.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

BoxStateBomb::BoxStateBomb(Box* pBox)
: pBox_(pBox)
{
    
}

BoxStateBomb::~BoxStateBomb()
{
    
}

void BoxStateBomb::enter()
{
    SimpleAudioEngine::getInstance()->playEffect("effect_set_bomb.mp3");
    pBox_->getBoxStateCurrent()->exit();
    pBox_->getBoxSprite()->setSpriteFrame("box_0_opened_0.png");
    pBox_->setBoxStateCurrent(this);
}

void BoxStateBomb::exit()
{
    
}