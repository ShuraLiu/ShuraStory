//
//  PlayLayer.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-22.
//
//

#ifndef __mygame__PlayLayer__
#define __mygame__PlayLayer__

#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;

class GameLogic;

class PlayLayer
: public cocos2d::Layer
{
public:
    PlayLayer();
    virtual ~PlayLayer();
    
    CREATE_FUNC(PlayLayer);
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
public:
    void setGameLogic(GameLogic* pLogic)
    {
        pLogic_ = pLogic;
    }
    
private:
    GameLogic* pLogic_;
    EventListenerTouchOneByOne* pListrener_;
};

class PlayLayerLoader : public cocosbuilder::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PlayLayerLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PlayLayer);
    
    static const char* layerClassName()
    {
        return "PlayLayer";
    }
};

#endif /* defined(__mygame__PlayLayer__) */
