//
//  RoleState.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#ifndef __mygame__RoleState__
#define __mygame__RoleState__

class RoleState
{
public:
    virtual void enter() = 0;
    virtual void exit() = 0;
    
public:
    virtual ~RoleState(){};
};

#endif /* defined(__mygame__RoleState__) */
