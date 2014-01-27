//
//  ActorProperty.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#ifndef __mygame__ActorProperty__
#define __mygame__ActorProperty__

#include "cocos2d.h"

USING_NS_CC;

class ActorProperty
{
public:
    std::string name;
    std::string action_idle;
    std::string action_move;
    std::string action_attack;
    std::string action_attacked;
    std::string action_climb;
    std::string action_dead;
    
    Rect bodyRect;
    Rect leftAttackRect;
    Rect rightAttackRect;
    std::string direction;
    
public:
    ActorProperty()
    : bodyRect(Rect::ZERO)
    , leftAttackRect(Rect::ZERO)
    , rightAttackRect(Rect::ZERO)
    {
        
    }
    ~ActorProperty(){};
};

#endif /* defined(__mygame__ActorProperty__) */
