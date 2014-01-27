//
//  RoleStateAttack.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __mygame__RoleStateAttack__
#define __mygame__RoleStateAttack__

#include "BaseState.h"

class Role;

class RoleStateAttack
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit RoleStateAttack(Role* pRole);
    virtual ~RoleStateAttack();
    
private:
    Role* pRole_;
};

#endif /* defined(__mygame__RoleStateAttack__) */
