//
//  AIStateRevival.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#ifndef __ShuraStory__AIStateRevival__
#define __ShuraStory__AIStateRevival__

#include "BaseState.h"

class AI;

class AIStateRevival
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
public:
    explicit AIStateRevival(AI* pAI);
    virtual ~AIStateRevival();
    
private:
    AI* pAI_;
};

#endif /* defined(__ShuraStory__AIStateRevival__) */
