//
//  BaseState.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __ShuraStory__RoleState__
#define __ShuraStory__RoleState__

class BaseState
{
public:
    virtual void enter() = 0;
    virtual void exit() = 0;
    
public:
    virtual ~BaseState(){};
};

#endif /* defined(__ShuraStory__RoleState__) */
