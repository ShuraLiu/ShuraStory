//
//  AIStateMove.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#ifndef __mygame__AIStateMove__
#define __mygame__AIStateMove__

#include "RoleState.h"

class AI;

class AIStateMove
: public RoleState
{
public:
    virtual void enter();
    virtual void exit();
    virtual void init();
    virtual void update(float delta);
    
public:
    explicit AIStateMove(AI* pAI);
    virtual ~AIStateMove();
    
private:
    AI* pAI_;
};

#endif /* defined(__mygame__AIStateMove__) */
