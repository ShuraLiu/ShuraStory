//
//  RoleStateVictory.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#ifndef __ShuraStory__RoleStateVictory__
#define __ShuraStory__RoleStateVictory__

#include "BaseState.h"

class Role;

class RoleStateVictory
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit RoleStateVictory(Role* pRole);
    virtual ~RoleStateVictory();
    
private:
    Role* pRole_;
};

#endif /* defined(__ShuraStory__RoleStateVictory__) */
