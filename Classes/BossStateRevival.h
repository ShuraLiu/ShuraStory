//
//  BossStateRevival.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#ifndef __ShuraStory__BossStateRevival__
#define __ShuraStory__BossStateRevival__

#include "BaseState.h"

class Boss;

class BossStateRevival
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit BossStateRevival(Boss* pBoss);
    virtual ~BossStateRevival();
    
private:
    Boss* pBoss_;
};

#endif /* defined(__ShuraStory__BossStateRevival__) */
