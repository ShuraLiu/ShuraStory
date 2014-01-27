//
//  BoxStateIdle.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#ifndef __ShuraStory__BoxStateIdle__
#define __ShuraStory__BoxStateIdle__

#include "BaseState.h"

class Box;

class BoxStateIdle
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit BoxStateIdle(Box* pBox);
    virtual ~BoxStateIdle();
    
private:
    Box* pBox_;
};

#endif /* defined(__ShuraStory__BoxStateIdle__) */
