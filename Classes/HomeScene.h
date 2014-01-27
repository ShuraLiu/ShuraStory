//
//  HomeScene.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-26.
//
//

#ifndef __ShuraStory__HomeScene__
#define __ShuraStory__HomeScene__

#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"

class HomeScene
: public cocos2d::Layer
, public cocosbuilder::CCBSelectorResolver
{
    
public:
    HomeScene();
    virtual ~HomeScene();
    
public:
    CREATE_FUNC(HomeScene);
    
private:
    void onMenuPlay(cocos2d::Object* obj);
    
public:
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char* pSelectorName);
};

class HomeSceneLoader : public cocosbuilder::LayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HomeSceneLoader, loader);
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HomeScene);
    static const char* layerClassName()
    {
        return "HomeScene";
    }
};

#endif /* defined(__ShuraStory__HomeScene__) */
