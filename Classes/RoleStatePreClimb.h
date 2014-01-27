//
//  RoleStatePreClimb.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#ifndef __mygame__RoleStatePreClimb__
#define __mygame__RoleStatePreClimb__

#include "RoleState.h"

class Role;

class RoleStatePreClimb
: public RoleState
{
public:
    virtual void enter();
    virtual void exit();
    virtual void init();
    virtual void update(float delta);
    
public:
    explicit RoleStatePreClimb(Role* pRole);
    virtual ~RoleStatePreClimb();
    
private:
    Role* pRole_;
};

#endif /* defined(__mygame__RoleStatePreClimb__) */
