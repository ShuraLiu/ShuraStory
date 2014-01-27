//
//  HomeScene.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-26.
//
//

#include "HomeScene.h"
#include "Game.h"

USING_NS_CC;
using namespace cocosbuilder;

HomeScene::HomeScene()
{
    
}

HomeScene::~HomeScene()
{
    
}

void HomeScene::onMenuPlay(cocos2d::Object* obj)
{
    Game::getInstance().switchActivity(READY_TO_PLAY);
}

cocos2d::SEL_MenuHandler HomeScene::onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuPlay", HomeScene::onMenuPlay);
    return nullptr;
}

cocos2d::extension::Control::Handler HomeScene::onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char* pSelectorName)
{
    return nullptr;
}