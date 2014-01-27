//
//  Wall.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-24.
//
//

#ifndef __ShuraStory__Wall__
#define __ShuraStory__Wall__

#include "SceneObject.h"
#include "cocos2d.h"

class Wall : public SceneObject
{
public:
    Wall(){};
    virtual ~Wall(){};
    
    CC_SYNTHESIZE(cocos2d::Rect, collisionRect_, CollisionRect);
    
    float getLeftX()
    {
        return collisionRect_.getMinX();
    };
    
    float getRightX()
    {
        return collisionRect_.getMaxX();
    }
};

#endif /* defined(__ShuraStory__Wall__) */
