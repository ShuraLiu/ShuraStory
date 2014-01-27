//
//  AIStateDead.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __mygame__AIStateDead__
#define __mygame__AIStateDead__

#include "BaseState.h"

class AI;

class AIStateDead
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit AIStateDead(AI* pAI);
    virtual ~AIStateDead();
    
private:
    AI* pAI_;
};

#endif /* defined(__mygame__AIStateDead__) */
