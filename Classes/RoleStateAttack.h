//
//  RoleStateAttack.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __mygame__RoleStateAttack__
#define __mygame__RoleStateAttack__

#include "RoleState.h"

class Role;

class RoleStateAttack
: public RoleState
{
public:
    virtual void enter();
    virtual void exit();
    virtual void init();
    virtual void update(float delta);
    
public:
    explicit RoleStateAttack(Role* pRole);
    virtual ~RoleStateAttack();
    
private:
    Role* pRole_;
};

#endif /* defined(__mygame__RoleStateAttack__) */
