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
        LEFT,
        RIGHT
    };
public:
    Actor(){};
    virtual ~Actor(){};
    
    CC_SYNTHESIZE(Direction, direction_, Direction);
protected:
//    Direction direction_;
    Direction initialDirection_;
};

#endif /* defined(__ShuraStory__Actor__) */
