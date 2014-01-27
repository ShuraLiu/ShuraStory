//
//  BoxStateReadyToOpen.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#ifndef __ShuraStory__BoxStateReadyToOpen__
#define __ShuraStory__BoxStateReadyToOpen__

#include "BaseState.h"

class Box;

class BoxStateReadyToOpen
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit BoxStateReadyToOpen(Box* pBox);
    virtual ~BoxStateReadyToOpen();
    
private:
    Box* pBox_;
};

#endif /* defined(__ShuraStory__BoxStateReadyToOpen__) */
