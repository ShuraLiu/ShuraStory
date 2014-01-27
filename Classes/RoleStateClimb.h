//
//  RoleStateClimb.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#ifndef __mygame__RoleStateClimb__
#define __mygame__RoleStateClimb__

#include "RoleState.h"

class Role;

class RoleStateClimb
: public RoleState
{
public:
    virtual void enter();
    virtual void exit();
    virtual void init();
    virtual void update(float delta);
    
public:
    explicit RoleStateClimb(Role* pRole);
    virtual ~RoleStateClimb();
    
private:
    Role* pRole_;
};

#endif /* defined(__mygame__RoleStateClimb__) */
