/*
 * LoadingScene.h
 *
 *  Created on: 2013-12-10
 *      Author: shura
 */

#ifndef LoadingScene_H_
#define LoadingScene_H_

#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"
#include "LoadLogic.h"

class LoadingScene
: public cocos2d::Layer
, public LoadLogic::IObserver
, public cocosbuilder::CCBMemberVariableAssigner{

	cocos2d::Node* pNodeLoading_;
    LoadLogic logic_;

public:
    LoadingScene();
    virtual ~LoadingScene();

public:
    CREATE_FUNC(LoadingScene);

    // CCLayer
    virtual bool init();
    virtual void update(float delta);

private:
    void animationCallback();

public:
    // LoadLogic::IObserver
    virtual void onStatusChanged(LoadLogic::LoadStatus prevStatus, LoadLogic::LoadStatus status);

public:
    //CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(cocos2d::Object* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode);
};

class LoadingSceneLoader : public cocosbuilder::LayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LoadingSceneLoader, loader);
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LoadingScene);
    static const char* layerClassName()
    {
        return "LoadingScene";
    }
};

#endif /* LoadingScene_H_ */
