//
//  GameOverScene.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-26.
//
//

#include "GameOverScene.h"
#include "Game.h"
#include "GameContext.h"

USING_NS_CC;
using namespace cocosbuilder;

GameOverScene::GameOverScene()
{
    
}

GameOverScene::~GameOverScene()
{
    
}

void GameOverScene::onMenuRestart(cocos2d::Object* obj)
{
    GameContext::getInstance().resetMapInfo();
    Game::getInstance().switchActivity(LOADING_FINISHED);
}

cocos2d::SEL_MenuHandler GameOverScene::onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuReStart", GameOverScene::onMenuRestart);
    return nullptr;
}

cocos2d::extension::Control::Handler GameOverScene::onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char* pSelectorName)
{
    return nullptr;
}