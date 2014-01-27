//
//  BossStateMove.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#ifndef __mygame__BossStateMove__
#define __mygame__BossStateMove__

#include "BaseState.h"

class Boss;

class BossStateMove
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit BossStateMove(Boss* pBoss);
    virtual ~BossStateMove();
    
private:
    Boss* pBoss_;
};

#endif /* defined(__mygame__BossStateMove__) */
