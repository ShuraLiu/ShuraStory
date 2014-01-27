//
//  BossStateDead.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __mygame__BossStateDead__
#define __mygame__BossStateDead__

#include "BaseState.h"

class Boss;

class BossStateDead
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit BossStateDead(Boss* pBoss);
    virtual ~BossStateDead();
    
private:
    Boss* pBoss_;
};

#endif /* defined(__mygame__BossStateDead__) */
