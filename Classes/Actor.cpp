//
//  Actor.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#include "Actor.h"

Actor::Actor()
: actorSprite_(cocos2d::Sprite::create())
, direction_(NONE)
{
	CC_SAFE_RETAIN(actorSprite_);
}

Actor::~Actor()
{
	CC_SAFE_RELEASE_NULL(actorSprite_);
}