//
//  BoxStateOpening.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#ifndef __ShuraStory__BoxStateOpening__
#define __ShuraStory__BoxStateOpening__

#include "BaseState.h"

class Box;

class BoxStateOpening
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit BoxStateOpening(Box* pBox);
    virtual ~BoxStateOpening();
    
private:
    Box* pBox_;
};

#endif /* defined(__ShuraStory__BoxStateOpening__) */
