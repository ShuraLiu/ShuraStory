//
//  GameOverScene.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-26.
//
//

#ifndef __ShuraStory__GameOverScene__
#define __ShuraStory__GameOverScene__

#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"

class GameOverScene
: public cocos2d::Layer
, public cocosbuilder::CCBSelectorResolver
{
    
public:
    GameOverScene();
    virtual ~GameOverScene();
    
public:
    CREATE_FUNC(GameOverScene);
    
private:
    void onMenuRestart(cocos2d::Object* obj);
    
public:
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char* pSelectorName);
};

class GameOverSceneLoader : public cocosbuilder::LayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameOverSceneLoader, loader);
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameOverScene);
    static const char* layerClassName()
    {
        return "GameOverScene";
    }
};

#endif /* defined(__ShuraStory__GameOverScene__) */
