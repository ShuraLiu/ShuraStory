//
//  AIStateInitial.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __ShuraStory__AIStateInitial__
#define __ShuraStory__AIStateInitial__

#include "BaseState.h"

class AI;

class AIStateInitial
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();    
public:
    explicit AIStateInitial(AI* pAI);
    virtual ~AIStateInitial();
    
private:
    AI* pAI_;
};

#endif /* defined(__ShuraStory__AIStateInitial__) */
