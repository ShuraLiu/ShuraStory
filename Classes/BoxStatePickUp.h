//
//  BoxStatePickUp.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#ifndef __ShuraStory__BoxStatePickUp__
#define __ShuraStory__BoxStatePickUp__

#include "BaseState.h"

class Box;

class BoxStatePickUp
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit BoxStatePickUp(Box* pBox);
    virtual ~BoxStatePickUp();
    
private:
    Box* pBox_;
};

#endif /* defined(__ShuraStory__BoxStatePickUp__) */
