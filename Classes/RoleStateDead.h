//
//  RoleStateDead.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __ShuraStory__RoleStateDead__
#define __ShuraStory__RoleStateDead__

#include "BaseState.h"

class Role;

class RoleStateDead
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit RoleStateDead(Role* pRole);
    virtual ~RoleStateDead();
    
private:
    Role* pRole_;
};

#endif /* defined(__ShuraStory__RoleStateDead__) */
