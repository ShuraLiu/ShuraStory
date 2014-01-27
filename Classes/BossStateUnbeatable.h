//
//  BossStateUnbeatable.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#ifndef __ShuraStory__BossStateUnbeatable__
#define __ShuraStory__BossStateUnbeatable__

#include "BaseState.h"

class Boss;

class BossStateUnbeatable
: public BaseState
{
public:
    virtual void enter();
    virtual void exit();
    
public:
    explicit BossStateUnbeatable(Boss* pBoss);
    virtual ~BossStateUnbeatable();
    
private:
    Boss* pBoss_;
};

#endif /* defined(__ShuraStory__BossStateUnbeatable__) */
