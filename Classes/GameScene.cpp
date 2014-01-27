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
#include "Box.h"
#include "GameContext.h"
#include "Boss.h"

USING_NS_CC;
using namespace cocosbuilder;

static const int BOMB_ACTION_TAG = 901;

GameScene::GameScene()
: logic_(*this)
, pLayerGame_(0)
, pLayerControl_(0)
, pSpriteBomb_(0)
, pSpriteLight0_(0)
, pSpriteLight1_(0)
, pSpriteLight2_(0)
, pLayerBomb_(0)
{

}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE_NULL(pLayerGame_);
    CC_SAFE_RELEASE_NULL(pLayerControl_);
    CC_SAFE_RELEASE_NULL(pLayerBomb_);
}

void GameScene::onEnter()
{
    Layer::onEnter();
    pLayerControl_->setGameLogic(&logic_);
    scheduleUpdate();
    
    ClippingNode* pClip=ClippingNode::create();
    pClip->setContentSize(getContentSize());
    addChild(pClip);
    //加入灰色的底板
    LayerColor* pColor= LayerColor::create(Color4B(0, 0, 0, 255));
    pClip->addChild(pColor);
    
    DrawNode *m_pAA=DrawNode::create();
    static Color4F green = {0, 1, 0, 1};
    Size size = pLayerGame_->getContentSize();
    Point pos = pLayerGame_->getPosition();
    static Point rect[4]=
    {
        Point(-size.width / 2, size.height / 2),
        Point(size.width / 2, size.height / 2),
        Point(size.width / 2,-size.height / 2),
        Point(-size.width / 2,-size.height / 2)
    };
    m_pAA->drawPolygon(rect, 4, green, 0, green);
    m_pAA->setPosition(Point(getContentSize().width/2, getContentSize().height/2));
    //设置为pclip的模板
    pClip->setStencil(m_pAA);
    pClip->setInverted(true);
}

void GameScene::update(float delta)
{
    logic_.update(delta);
}

void GameScene::onLadderCanClimb(Ladder *ladder, bool isCanUp)
{
    if (isCanUp)
    {
        CCLOG("[%f][%f]", ladder->getMenuUp()->getPositionX(), ladder->getMenuUp()->getPositionY());
        pLayerGame_->addChild(ladder->getMenuUp(), ROLE_Z_ORDER + 1);
    }
    else
    {
        pLayerGame_->addChild(ladder->getMenuDown(), ROLE_Z_ORDER + 1);
    }
//    Sprite* normalSprite = 0;// Sprite::createWithSpriteFrameName("button_ladder_normal.png");
//    Sprite* selectedSprite = 0;// Sprite::createWithSpriteFrameName("button_ladder_normal.png");
//    if (isCanUp)
//    {
//        normalSprite = Sprite::createWithSpriteFrameName("button_ladder_normal_0.png");
//        selectedSprite = Sprite::createWithSpriteFrameName("button_ladder_normal_0.png");
//    }
//    else
//    {
//        normalSprite = Sprite::createWithSpriteFrameName("button_ladder_normal_1.png");
//        selectedSprite = Sprite::createWithSpriteFrameName("button_ladder_normal_1.png");
//    }
//    MenuItemSprite* item = MenuItemSprite::create(normalSprite, selectedSprite, CC_CALLBACK_1(GameScene::onMenuClimb, this));
//    item->setAnchorPoint(Point(0.5, 0.5));
//    item->setPosition(Point::ZERO);
//    item->setUserObject(ladder);
//    
//    cocos2d::Menu* pMenu = Menu::create(item, NULL);
//    pMenu->ignoreAnchorPointForPosition(false);
//    pMenu->setAnchorPoint(Point::ZERO);
//    Sprite* pSpriteLadder = ladder->getSpriteLadder();
//    Sprite*temp = Sprite::createWithSpriteFrameName("button_ladder_normal_0.png");
//    if (isCanUp)
//    {
//        pMenu->setPosition(Point(pSpriteLadder->getPositionX() + pSpriteLadder->getContentSize().width / 2, pSpriteLadder->getPositionY() + temp->getContentSize().height / 2));
//    }
//    else
//    {
//        pMenu->setPosition(Point(pSpriteLadder->getPositionX() + pSpriteLadder->getContentSize().width / 2, pSpriteLadder->getPositionY() + pSpriteLadder->getContentSize().height + temp->getContentSize().height / 2));
//    }
//    pLayerGame_->addChild(pMenu, ROLE_Z_ORDER - 1);
//    pMenu->setTag(ladder->getTag());
}

//void GameScene::onMenuClimb(cocos2d::Object *obj)
//{
//    Ladder* ladder = (Ladder*)((MenuItemSprite*) obj)->getUserObject();
//    logic_.climbLadder(ladder);
//}

void GameScene::onLadderCanNotClimb(Ladder *ladder)
{
    Menu* menu = ladder->getMenuDown();
    if (menu->getParent())
    {
        menu->removeFromParent();
    }
    menu = ladder->getMenuUp();
    if (menu->getParent())
    {
        menu->removeFromParent();
    }
}

void GameScene::onBoxCanOpen(Box *box)
{
    pLayerGame_->addChild(box->getMenuOpen(), ROLE_Z_ORDER + 1);
}

void GameScene::onBoxCanPickUp(Box *box)
{
    pLayerGame_->addChild(box->getMenuItems(), ROLE_Z_ORDER + 1);
}

void GameScene::onSwitchMap(TMXTiledMap* map)
{
    map->setPosition(Point(pLayerGame_->getContentSize().width, 0));
    pLayerGame_->addChild(map);
}

void GameScene::onSwitchMapProgressUpdate(float offset)
{
    pLayerGame_->setPositionX(pLayerGame_->getPositionX() + offset);
}

void GameScene::initLightAndBomb()
{
    Size size = pLayerBomb_->getContentSize();
    pSpriteLight0_ = Sprite::createWithSpriteFrameName("light_0.png");
    pSpriteLight0_->setPosition(Point(size.width * 0.03, size.height * 0.9375));
    pLayerBomb_->addChild(pSpriteLight0_, ROLE_Z_ORDER + 1);
    pSpriteLight1_ = Sprite::createWithSpriteFrameName("light_0.png");
    pSpriteLight1_->setPosition(Point(size.width * 0.07, size.height * 0.9375));
    pLayerBomb_->addChild(pSpriteLight1_, ROLE_Z_ORDER + 1);
    pSpriteLight2_ = Sprite::createWithSpriteFrameName("light_0.png");
    pSpriteLight2_->setPosition(Point(size.width * 0.11, size.height * 0.9375));
    pLayerBomb_->addChild(pSpriteLight2_, ROLE_Z_ORDER + 1);
    pSpriteBomb_ = Sprite::createWithSpriteFrameName("bomb_idle.png");
    pSpriteBomb_->setPosition(Point(size.width * 0.174, size.height * 0.9375));
    pLayerBomb_->addChild(pSpriteBomb_, ROLE_Z_ORDER + 1);
    
    pSpriteBombExplode_ = Sprite::createWithSpriteFrameName("bomb_idle.png");
    pSpriteBombExplode_->setPosition(Point(size.width * 0.174, size.height * 0.9375));
    pLayerBomb_->addChild(pSpriteBombExplode_, ROLE_Z_ORDER + 1);
    RepeatForever* action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("bomb_jump")));
    action->setTag(BOMB_ACTION_TAG);
    pSpriteBombExplode_->runAction(action);
    pSpriteBombExplode_->setVisible(false);
    GameContext::getInstance().setBombInitialRect(Rect(pSpriteBomb_->getPositionX() - pSpriteBomb_->getContentSize().width / 2, pSpriteBomb_->getPositionY() - pSpriteBomb_->getContentSize().height / 2, pSpriteBomb_->getContentSize().width, pSpriteBomb_->getContentSize().height));
    GameContext::getInstance().setBombMovedRect(GameContext::getInstance().getBombInitialRect());
    
    pLabelBombCount_ = LabelTTF::create(std::string("x0"), "", CCBReader::getResolutionScale() * 15);
    pLabelBombCount_->setAnchorPoint(Point(0, 0.5));
    pLabelBombCount_->setPosition(Point(size.width * 0.213, size.height * 0.92));
    pLayerBomb_->addChild(pLabelBombCount_, ROLE_Z_ORDER + 1);
}

void GameScene::updateLightAndBomb(unsigned int count)
{
    int localCount = count % 4;
    int bombCount = count / 4;
    pSpriteLight0_->setSpriteFrame((localCount > 0) ? "light_1.png" : "light_0.png");
    pSpriteLight1_->setSpriteFrame((localCount > 1) ? "light_1.png" : "light_0.png");
    pSpriteLight2_->setSpriteFrame((localCount > 2) ? "light_1.png" : "light_0.png");
    std::stringstream ss;
    std::string str;
    ss << "x";
    ss << bombCount;
    ss >> str;
    pLabelBombCount_->setString(str.c_str());
    if (bombCount > 0)
    {
        if (!pSpriteBomb_->getActionByTag(BOMB_ACTION_TAG))
        {
            RepeatForever* action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("bomb_jump")));
            action->setTag(BOMB_ACTION_TAG);
            pSpriteBomb_->runAction(action);
        }
    }
    else
    {
        pSpriteBomb_->stopAllActions();
    }
    if (bombCount == 0)
    {
        pSpriteBomb_->setSpriteFrame("bomb_idle.png");
    }
}

void GameScene::onBombMoved(const cocos2d::Point &add)
{
    pSpriteBombExplode_->setVisible(true);
    Point pos = pSpriteBombExplode_->getPosition();
    pSpriteBombExplode_->setPosition(pos + add);
}

void GameScene::onBombExplode()
{
//    GameContext& context = GameContext::getInstance();
    Animate* action = Animate::create(AnimationCache::getInstance()->getAnimation("bomb_bomb"));
    CallFunc* func = CallFunc::create(CC_CALLBACK_0(GameScene::onBombExplodeFinished, this));
    Sequence* seq = Sequence::create(action,func, NULL);
    pSpriteBombExplode_->stopAllActions();
    pSpriteBombExplode_->runAction(seq);
//    pSpriteBombExplode_->setPosition(Point(context.getBombInitialRect().getMidX(), context.getBombInitialRect().getMidY()));
//    pSpriteBombExplode_->setVisible(false);
}

void GameScene::onBombExplodeFinished()
{
    GameContext& context = GameContext::getInstance();
    pSpriteBombExplode_->stopAllActions();
    RepeatForever* action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("bomb_jump")));
    action->setTag(BOMB_ACTION_TAG);
    pSpriteBombExplode_->runAction(action);
    pSpriteBombExplode_->setVisible(false);
    pSpriteBombExplode_->setPosition(Point(context.getBombInitialRect().getMidX(), context.getBombInitialRect().getMidY()));
}

void GameScene::moveLayerUp()
{
    pLayerControl_->onExit();
    GameContext::getInstance().setCurrentOffsetY(GameContext::getInstance().getCurrentOffsetY() + GameContext::getInstance().getOffsetYChangeOnce());
    MoveBy* moveBy = MoveBy::create(1, Point(0, -GameContext::getInstance().getOffsetYChangeOnce()));
    CallFunc* func = CallFunc::create(CC_CALLBACK_0(GameScene::onMoveLayerFinished, this));
    Sequence* seq = Sequence::create(moveBy, func, NULL);
    pLayerGame_->runAction(seq);
}

void GameScene::moveLayerDown()
{
    pLayerControl_->onExit();
    GameContext::getInstance().setCurrentOffsetY(GameContext::getInstance().getCurrentOffsetY() - GameContext::getInstance().getOffsetYChangeOnce());
    MoveBy* moveBy = MoveBy::create(1, Point(0, GameContext::getInstance().getOffsetYChangeOnce()));
    CallFunc* func = CallFunc::create(CC_CALLBACK_0(GameScene::onMoveLayerFinished, this));
    Sequence* seq = Sequence::create(moveBy, func, NULL);
    pLayerGame_->runAction(seq);
}

void GameScene::onMoveLayerFinished()
{
    logic_.setChangeY(false);
    pLayerControl_->onEnter();
}

void GameScene::onBossItemShowed(Boss *boss)
{
    Menu* pMenuItem_ = boss->getMenuPass();
    Sprite* pBossSprite_ = boss->getBossSprite();
    pMenuItem_->setPosition(Point(pBossSprite_->getPositionX() + pBossSprite_->getContentSize().width / 2, pBossSprite_->getPositionY() - pBossSprite_->getContentSize().height / 3));
    pLayerGame_->addChild(boss->getMenuPass(), ROLE_Z_ORDER + 1);
}

void GameScene::onBossItemPickUped()
{
    std::string mapName = GameContext::getInstance().getMapName();
    if (0 == std::strcmp("game_0.tmx", mapName.c_str()))
    {
        Sprite* sprite = Sprite::createWithSpriteFrameName("eye.png");
        sprite->setAnchorPoint(Point(0.5, 0));
        sprite->setPosition(Point(pLayerGame_->getContentSize().width * 0.5, pLayerGame_->getContentSize().height * 0.45));
        pLayerGame_->addChild(sprite);
    }
    else if (0 == std::strcmp("game_1.tmx", mapName.c_str()))
    {
        Sprite* sprite = Sprite::createWithSpriteFrameName("eye_1.png");
        sprite->setAnchorPoint(Point::ZERO);
        sprite->setPosition(Point(pLayerGame_->getContentSize().width * 0.5885, pLayerGame_->getContentSize().height * 0.067));
        pLayerGame_->addChild(sprite);
    }
    else if (0 == std::strcmp("game_2.tmx", mapName.c_str()))
    {
        Sprite* sprite = Sprite::createWithSpriteFrameName("eye_2.png");
        sprite->setAnchorPoint(Point::ZERO);
        sprite->setPosition(Point(pLayerGame_->getContentSize().width * 0.0552, 891));
        pLayerGame_->addChild(sprite);
    }
    else if (0 == std::strcmp("game_3.tmx", mapName.c_str()))
    {
        Sprite* sprite = Sprite::createWithSpriteFrameName("eye_3.png");
        sprite->setAnchorPoint(Point::ZERO);
        sprite->setPosition(Point(165, 1156));
        pLayerGame_->addChild(sprite);
    }
    else if (0 == std::strcmp("game_3.tmx", mapName.c_str()))
    {
        Sprite* sprite = Sprite::createWithSpriteFrameName("eye_3.png");
        sprite->setAnchorPoint(Point::ZERO);
        sprite->setPosition(Point(37, 1798));
        pLayerGame_->addChild(sprite);
    }
}

void GameScene::showVictoryAnimation(cocos2d::Sprite* sprite)
{
    sprite->setPosition(Point(pLayerBomb_->getContentSize().width / 2, pLayerBomb_->getContentSize().height / 2));
    pLayerBomb_->addChild(sprite);
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
            pLayerControl_->onExit();
            GameContext::getInstance().initData();
            logic_.addMapToLayer(pLayerGame_);
            initLightAndBomb();
        }
            break;
        case GameLogic::GAME_STATUS_PLAYING:
        {
            pLayerControl_->onEnter();
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
        case GameLogic::GAME_STATUS_VICTORY:
        {
            pLayerControl_->onExit();
        }
            break;
        case GameLogic::GAME_STATUS_SWITCH_MAP:
        {
            if (pLayerControl_->isRunning())
            {
                pLayerControl_->onExit();
            }
        }
            break;
        case GameLogic::GAME_STATUS_LOAD_NEXT_MAP:
        {
            pLayerGame_->setPosition(getContentSize().width / 2, getContentSize().height / 2);
            pLayerGame_->removeAllChildren();
            pLayerBomb_->removeAllChildren();
        }
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
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "layerBomb", Layer*, pLayerBomb_);
    return false;
}

void GameScene::onNodeLoaded(cocos2d::Node * pNode, cocosbuilder::NodeLoader * pNodeLoader)
{
    
}

