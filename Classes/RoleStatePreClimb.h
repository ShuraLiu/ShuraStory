//
//  RoleStatePreClimb.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#ifndef __mygame__RoleStatePreClimb__
#define __mygame__RoleStatePreClimb__

#include "BaseState.h"

class Role;

class RoleStatePreClimb
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit RoleStatePreClimb(Role* pRole);
    virtual ~RoleStatePreClimb();
    
private:
    Role* pRole_;
};

#endif /* defined(__mygame__RoleStatePreClimb__) */
