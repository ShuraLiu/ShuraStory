//
//  GameScene.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#include "GameScene.h"
#include "PlayLayer.h"
#include "Ladder.h"
#include "config.h"

USING_NS_CC;
using namespace cocosbuilder;

GameScene::GameScene()
: logic_(*this)
, pLayerGame_(0)
, pLayerControl_(0)
{
    
}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE_NULL(pLayerGame_);
    CC_SAFE_RELEASE_NULL(pLayerControl_);
}

void GameScene::onEnter()
{
    Layer::onEnter();
    pLayerControl_->setGameLogic(&logic_);
    scheduleUpdate();
}

void GameScene::update(float delta)
{
    logic_.update(delta);
}

void GameScene::onLadderCanClimb(Ladder *ladder, bool isCanUp)
{
    Sprite* normalSprite = 0;// Sprite::createWithSpriteFrameName("button_ladder_normal.png");
    Sprite* selectedSprite = 0;// Sprite::createWithSpriteFrameName("button_ladder_normal.png");
    if (isCanUp)
    {
        normalSprite = Sprite::createWithSpriteFrameName("button_ladder_normal_0.png");
        selectedSprite = Sprite::createWithSpriteFrameName("button_ladder_normal_0.png");
    }
    else
    {
        normalSprite = Sprite::createWithSpriteFrameName("button_ladder_normal_1.png");
        selectedSprite = Sprite::createWithSpriteFrameName("button_ladder_normal_1.png");
    }
    MenuItemSprite* item = MenuItemSprite::create(normalSprite, selectedSprite, CC_CALLBACK_1(GameScene::onMenuClimb, this));
    item->setAnchorPoint(Point(0.5, 0.5));
    item->setPosition(Point::ZERO);
    item->setUserObject(ladder);
    
    cocos2d::Menu* pMenu = Menu::create(item, NULL);
    pMenu->ignoreAnchorPointForPosition(false);
    pMenu->setAnchorPoint(Point::ZERO);
    Sprite* pSpriteLadder = ladder->getSpriteLadder();
    pMenu->setPosition(Point(pSpriteLadder->getPositionX() + pSpriteLadder->getContentSize().width / 2, pSpriteLadder->getPositionY() + pSpriteLadder->getContentSize().height / 2));
    pLayerGame_->addChild(pMenu, ROLE_Z_ORDER - 1);
    pMenu->setTag(ladder->getTag());
}

void GameScene::onMenuClimb(cocos2d::Object *obj)
{
    Ladder* ladder = (Ladder*)((MenuItemSprite*) obj)->getUserObject();
    logic_.climbLadder(ladder);
}

void GameScene::onLadderCanNotClimb(Ladder *ladder)
{
    if (pLayerGame_->getChildByTag(ladder->getTag()))
    {
        pLayerGame_->removeChildByTag(ladder->getTag());
    }
}

void GameScene::onAICanAttack()
{
    
}

void GameScene::onStatusChanged(GameLogic::GameStatus prevStatus, GameLogic::GameStatus status)
{
    switch (status)
    {
        case GameLogic::GAME_STATUS_NONE:
        {
            
        }
            break;
        case GameLogic::GAME_STATUS_INIT:
        {
            logic_.addMapToLayer(pLayerGame_);
        }
            break;
        case GameLogic::GAME_STATUS_PLAYING:
        {
            
        }
            break;
        case GameLogic::GAME_STATUS_PAUSE:
        {
            
        }
            break;
        case GameLogic::GAME_STATUS_END:
        {
            
        }
            break;
        default:
            break;
    }
}

SEL_MenuHandler GameScene::onResolveCCBCCMenuItemSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    return nullptr;
}

cocos2d::extension::Control::Handler GameScene::onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char* pSelectorName)
{
    return nullptr;
}

bool GameScene::onAssignCCBMemberVariable(cocos2d::Object* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "layerGame", Layer*, pLayerGame_);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "layerControl", PlayLayer*, pLayerControl_);
    return false;
}

void GameScene::onNodeLoaded(cocos2d::Node * pNode, cocosbuilder::NodeLoader * pNodeLoader)
{
    
}

