//
//  SceneObject.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-22.
//
//

#ifndef __mygame__SceneObject__
#define __mygame__SceneObject__

#include "cocos2d.h"

class SceneObject : public cocos2d::Object
{
public:
    SceneObject(){};
    virtual ~SceneObject(){};

    virtual void addToLayer(cocos2d::Layer* layer){};
};

#endif /* defined(__mygame__SceneObject__) */
