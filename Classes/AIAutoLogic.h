//
//  AIAutoLogic.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-26.
//
//

#ifndef __ShuraStory__AIAutoLogic__
#define __ShuraStory__AIAutoLogic__

#include "cocos2d.h"
#include "AI.h"

class AIAutoLogic
{
public:
    AIAutoLogic(AI* pAI);
    virtual ~AIAutoLogic();
    
    virtual void doAutoLogic(float delta) = 0;
    
    CC_SYNTHESIZE(AI*, pAI_, AI);
};

#endif /* defined(__ShuraStory__AIAutoLogic__) */
