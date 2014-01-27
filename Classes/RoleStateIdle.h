//
//  RoleStateIdle.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#ifndef __mygame__RoleStateIdle__
#define __mygame__RoleStateIdle__

#include "RoleState.h"

class Role;

class RoleStateIdle
: public RoleState
{
public:
    virtual void enter();
    virtual void exit();
    virtual void init();
    virtual void update(float delta);
    
public:
    explicit RoleStateIdle(Role* pRole);
    virtual ~RoleStateIdle();
    
private:
    Role* pRole_;
};

#endif /* defined(__mygame__RoleStateIdle__) */
