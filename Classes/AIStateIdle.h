//
//  AIStateIdle.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#ifndef __mygame__AIStateIdle__
#define __mygame__AIStateIdle__

#include "RoleState.h"

class AI;

class AIStateIdle
: public RoleState
{
public:
    virtual void enter();
    virtual void exit();
    virtual void init();
    virtual void update(float delta);
    
public:
    explicit AIStateIdle(AI* pAI);
    virtual ~AIStateIdle();
    
private:
    AI* pAI_;
};

#endif /* defined(__mygame__AIStateIdle__) */
