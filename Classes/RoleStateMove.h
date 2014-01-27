//
//  RoleStateMove.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-22.
//
//

#ifndef __mygame__RoleStateMove__
#define __mygame__RoleStateMove__

#include "BaseState.h"

class Role;

class RoleStateMove
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit RoleStateMove(Role* pRole);
    virtual ~RoleStateMove();
    
private:
    Role* pRole_;
};

#endif /* defined(__mygame__RoleStateMove__) */
