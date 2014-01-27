//
//  BoxStateBomb.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#ifndef __ShuraStory__BoxStateBomb__
#define __ShuraStory__BoxStateBomb__

#include "BaseState.h"

class Box;

class BoxStateBomb
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit BoxStateBomb(Box* pBox);
    virtual ~BoxStateBomb();
    
private:
    Box* pBox_;
};

#endif /* defined(__ShuraStory__BoxStateBomb__) */
