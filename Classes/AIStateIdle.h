//
//  AIStateIdle.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#ifndef __mygame__AIStateIdle__
#define __mygame__AIStateIdle__

#include "BaseState.h"

class AI;

class AIStateIdle
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit AIStateIdle(AI* pAI);
    virtual ~AIStateIdle();
    
private:
    AI* pAI_;
};

#endif /* defined(__mygame__AIStateIdle__) */
