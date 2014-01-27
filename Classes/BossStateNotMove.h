//
//  BossStateNotMove.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-26.
//
//

#ifndef __ShuraStory__BossStateNotMove__
#define __ShuraStory__BossStateNotMove__

#include "BaseState.h"

class Boss;

class BossStateNotMove
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit BossStateNotMove(Boss* pBoss);
    virtual ~BossStateNotMove();
    
private:
    Boss* pBoss_;
};

#endif /* defined(__ShuraStory__BossStateNotMove__) */
