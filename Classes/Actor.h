//
//  Actor.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __mygame__Actor__
#define __mygame__Actor__

class Actor
{
public:
    enum Direction
    {
        LEFT,
        RIGHT
    };
public:
    Actor(){};
    virtual ~Actor(){};
    
protected:
    Direction direction_;
};

#endif /* defined(__mygame__Actor__) */
