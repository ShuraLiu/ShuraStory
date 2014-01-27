//
//  BossStateIdle.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#ifndef __mygame__BossStateIdle__
#define __mygame__BossStateIdle__

#include "BaseState.h"

class Boss;

class BossStateIdle
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit BossStateIdle(Boss* pBoss);
    virtual ~BossStateIdle();
    
private:
    Boss* pBoss_;
};

#endif /* defined(__mygame__BossStateIdle__) */
