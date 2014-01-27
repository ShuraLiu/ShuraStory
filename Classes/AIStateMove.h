//
//  AIStateMove.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#ifndef __mygame__AIStateMove__
#define __mygame__AIStateMove__

#include "BaseState.h"

class AI;

class AIStateMove
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit AIStateMove(AI* pAI);
    virtual ~AIStateMove();
    
private:
    AI* pAI_;
};

#endif /* defined(__mygame__AIStateMove__) */
