//
//  AIStateAttack.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __mygame__AIStateAttack__
#define __mygame__AIStateAttack__

#include "RoleState.h"

class AI;

class AIStateAttack
: public RoleState
{
public:
    virtual void enter();
    virtual void exit();
    virtual void init();
    virtual void update(float delta);
    
public:
    explicit AIStateAttack(AI* pAI);
    virtual ~AIStateAttack();
    
private:
    AI* pAI_;
};

#endif /* defined(__mygame__AIStateAttack__) */
