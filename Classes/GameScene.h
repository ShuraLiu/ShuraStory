//
//  GameScene.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#ifndef __mygame__GameScene__
#define __mygame__GameScene__

#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"
#include "GameLogic.h"

class PlayLayer;

class GameScene
: public cocos2d::Layer
, public cocosbuilder::CCBSelectorResolver
, public cocosbuilder::CCBMemberVariableAssigner
, public cocosbuilder::NodeLoaderListener
, public GameLogic::IObserver
{
public:
    GameScene();
    virtual ~GameScene();
    
    CREATE_FUNC(GameScene);
    
    virtual void onEnter();
    virtual void update(float delta);
    
public:
    //cocosbuilder::CCBSelectorResolver
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char* pSelectorName);
    //cocosbuilder::CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(cocos2d::Object* target, const char* memberVariableName, cocos2d::Node* node);
    //cocosbuilder::NodeLoaderListener
    virtual void onNodeLoaded(cocos2d::Node * pNode, cocosbuilder::NodeLoader * pNodeLoader);
    //GameLogic::IObserver
    virtual void onStatusChanged(GameLogic::GameStatus prevStatus, GameLogic::GameStatus status);
    virtual void onLadderCanClimb(Ladder* ladder, bool isCanUp);
    virtual void onLadderCanNotClimb(Ladder* ladder);
    virtual void onAICanAttack();
    
private:
    void onMenuClimb(cocos2d::Object* obj);
    void onMenuAttack(cocos2d::Object* obj);
    
private:
    GameLogic logic_;
    PlayLayer* pLayerControl_;
    cocos2d::Layer* pLayerGame_;
};

class GameSceneLoader : public cocosbuilder::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameSceneLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameScene);
    
    static const char* layerClassName()
    {
        return "GameScene";
    }
};

#endif /* defined(__mygame__GameScene__) */
