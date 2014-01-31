//
//  Actor.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __ShuraStory__Actor__
#define __ShuraStory__Actor__

#include "cocos2d.h"

class Actor
{
public:
    enum Direction
    {
		NONE,
        LEFT,
        RIGHT,
		UP,
		DOWN,
    };
public:
    Actor();
    virtual ~Actor();

	virtual bool canBeAttack(){ return false; }
    
    CC_SYNTHESIZE(Direction, direction_, Direction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, actorSprite_, ActorSprite);
protected:
    Direction initialDirection_;
};

#endif /* defined(__ShuraStory__Actor__) */
