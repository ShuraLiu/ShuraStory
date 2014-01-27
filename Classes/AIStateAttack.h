//
//  AIStateAttack.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __mygame__AIStateAttack__
#define __mygame__AIStateAttack__

#include "BaseState.h"

class AI;

class AIStateAttack
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit AIStateAttack(AI* pAI);
    virtual ~AIStateAttack();
    
private:
    AI* pAI_;
};

#endif /* defined(__mygame__AIStateAttack__) */
