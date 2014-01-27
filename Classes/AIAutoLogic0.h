//
//  AIAutoLogic0.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-26.
//
//

#ifndef __ShuraStory__AIAutoLogic0__
#define __ShuraStory__AIAutoLogic0__

#include "AIAutoLogic.h"

class AIAutoLogic0 : public AIAutoLogic
{
public:
    AIAutoLogic0(AI* pAI);
    ~AIAutoLogic0();
    
    virtual void doAutoLogic(float delta);
};

#endif /* defined(__ShuraStory__AIAutoLogic0__) */
