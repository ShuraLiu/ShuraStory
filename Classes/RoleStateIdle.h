//
//  RoleStateIdle.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __ShuraStory__RoleStateIdle__
#define __ShuraStory__RoleStateIdle__

#include "BaseState.h"

class Role;

class RoleStateIdle
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit RoleStateIdle(Role* pRole);
    virtual ~RoleStateIdle();
    
private:
    Role* pRole_;
};

#endif /* defined(__ShuraStory__RoleStateIdle__) */
