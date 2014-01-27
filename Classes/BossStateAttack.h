//
//  BossStateAttack.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __mygame__BossStateAttack__
#define __mygame__BossStateAttack__

#include "BaseState.h"

class Boss;

class BossStateAttack
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit BossStateAttack(Boss* pBoss);
    virtual ~BossStateAttack();
    
private:
    Boss* pBoss_;
};

#endif /* defined(__mygame__BossStateAttack__) */
