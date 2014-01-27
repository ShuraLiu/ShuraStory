/*
 * LoadingScene.cpp
 *
 *  Created on: 2013-12-10
 *      Author: shura
 */

#include "LoadingScene.h"

USING_NS_CC;

LoadingScene::LoadingScene()
: pNodeLoading_(0)
, logic_(*this, PreloadList::getInstance())
{

}

LoadingScene::~LoadingScene()
{
	CC_SAFE_RELEASE_NULL(pNodeLoading_);
}

bool LoadingScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    scheduleUpdate();

    return true;
}

void LoadingScene::update(float delta)
{
    logic_.onLoadingFrame(delta);
}

void LoadingScene::onStatusChanged(LoadLogic::LoadStatus prevStatus, LoadLogic::LoadStatus status)
{
    switch (status)
    {
        case LoadLogic::LOAD_STATUS_NONE:
            break;
        case LoadLogic::LOAD_STATUS_LOADING_LOAD_BACKGROUND:
        {
//        	Sprite* pSpriteLoading = CCSprite::createWithSpriteFrameName("DAMO_UI_loading.png");
//        	pSpriteLoading->setPosition(pNodeLoading_->getPosition());
//        	addChild(pSpriteLoading);
        }
            break;
        case LoadLogic::LOAD_STATUS_LOADING_TEXTURE:

            break;
        case LoadLogic::LOAD_STATUS_LOADING_SPRITE_FRAME:

            break;
        case LoadLogic::LOAD_STATUS_LOADING_ANIMATION:

            break;
        case LoadLogic::LOAD_STATUS_LOADING_FONT:

            break;
        case LoadLogic::LOAD_STATUS_LOADING_BACKGROUND_MUSIC:

            break;
        case LoadLogic::LOAD_STATUS_LOADING_EFFECT:

            break;
        case LoadLogic::LOAD_STATUS_LOADING_PARTICLE:

            break;
        case LoadLogic::LOAD_STATUS_SUCCESSFULLY_FINISHED:
            break;
        case LoadLogic::LOAD_STATUS_ERROR:

            break;
    }
}

bool LoadingScene::onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode)
{
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeLoading", CCNode*, pNodeLoading_);
    return false;
}

