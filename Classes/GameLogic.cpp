//
//  GameLogic.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#include "GameLogic.h"
#include "GameContext.h"
#include "PlayLayer.h"
#include "Box.h"
#include "Boss.h"
#include "Game.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

GameLogic::GameLogic(IObserver& observer)
: observer_(observer)
, status_(GAME_STATUS_NONE)
, touch_(false)
, switchMapProgress_(0)
, switchMapSpeed_(320)
, changeY_(false)
, repeat_(0)
, sprite_(0)
, move_(false)
, bombMove_(false)
{
    
}

GameLogic::~GameLogic()
{
    CC_SAFE_RELEASE_NULL(repeat_);
    CC_SAFE_RELEASE_NULL(sprite_);
}

void GameLogic::update(float delta)
{
    switch (status_) {
        case GAME_STATUS_NONE:
        {
//            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
//            Director::getInstance()->getTextureCache()->addImage("game_1.pvr.ccz");
//            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
//            Director::getInstance()->getTextureCache()->addImage("map_background_2.png");
//            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_1.plist");
//            AnimationCache::getInstance()->addAnimationsWithFile("animations.plist");
            GameContext::getInstance().setGameLogic(this);
            GameContext::getInstance().initTiledMap(GameContext::getInstance().getCurrentMapName());
            GameStatus prevStatus = status_;
            status_ = GAME_STATUS_INIT;
            observer_.onStatusChanged(prevStatus, status_);
        }
            break;
        case GAME_STATUS_INIT:
        {
            GameStatus prevStatus = status_;
            status_ = GAME_STATUS_PLAYING;
            observer_.onStatusChanged(prevStatus, status_);
        }
            break;
        case GAME_STATUS_PLAYING:
        {
            GameContext& context = GameContext::getInstance();
            context.updateGameContext(delta);
            dealCollisionRoleAndBoss();
            dealCollsionRoleAndAI();
            dealCollisionRoleAndLadder();
            dealCollisionRoleAndBox();
            dealCollisionRoleAndWall();
            dealChangeMapOffsetY();
            checkMapPass();
        }
            break;
        case GAME_STATUS_VICTORY:
        {
            if (repeat_->isDone())
            {
                CC_SAFE_RELEASE_NULL(repeat_);
                sprite_->removeFromParent();
                CC_SAFE_RELEASE_NULL(sprite_);
                if (GameContext::getInstance().allMapFinished())
                {
                    Game::getInstance().switchActivity(GAME_OVER);
                    GameContext::getInstance().clear();
                }
                else
                {
                    GameContext::getInstance().goToNextMap();
                }

            }
//            if (GameContext::getInstance().getRole()->victoryAnimationFinished())
//            {
//                if (GameContext::getInstance().allMapFinished())
//                {
//                    Game::getInstance().switchActivity(GAME_OVER);
//                    GameContext::getInstance().clear();
//                }
//                else
//                {
//                    GameContext::getInstance().goToNextMap();
//                }
//            }
        }
            break;
        case GAME_STATUS_SWITCH_MAP:
        {
            float add = delta * switchMapSpeed_;
            switchMapProgress_ += add;
            if (switchMapProgress_ >= switchDistance_)
            {
                switchMapProgress_ = 0;
                GameStatus prevStatus = status_;
                status_ = GAME_STATUS_LOAD_NEXT_MAP;
                observer_.onStatusChanged(prevStatus, status_);
            }
            observer_.onSwitchMapProgressUpdate(-1 * add);
        }
            break;
        case GAME_STATUS_LOAD_NEXT_MAP:
        {
            GameContext::getInstance().initNextTiledMap();
            GameStatus prevStatus = status_;
            status_ = GAME_STATUS_INIT;
            observer_.onStatusChanged(prevStatus, status_);
        }
            break;
        default:
            break;
    }
}

void GameLogic::dealCollisionRoleAndBoss()
{
    GameContext& context = GameContext::getInstance();
    GameContext::BossArray& bossArray = context.getBossArray();
    Role* pRole = context.getRole();
    if (pRole->getCurrentState() != ROLE_STATE_PRE_CLIMB && pRole->getCurrentState() != ROLE_STATE_CLIMB && pRole->getCurrentState() != ROLE_STATE_DEAD)
    {
        for (int i = 0; i < bossArray.size(); ++i)
        {
            Boss* pBoss = bossArray.at(i);
            if (pBoss->getCurrentState() != BOSS_STATE_ATTACK  && pBoss->getCurrentState() != BOSS_STATE_DEAD && pBoss->getCurrentState() != BOSS_STATE_REVIVAL && checkCollision(pBoss->getAttackRect(), pRole->getBodyRect()))
            {
                pBoss->attack();
                pRole->dead();
            }
        }
        Boss* pBossToAttack = 0;
        for (int i = 0; i < bossArray.size(); ++i)
        {
            Boss* pBoss = bossArray.at(i);
            if ( pBoss->canBeAttack()
                && (pBoss->getCurrentState() == BOSS_STATE_IDLE || pBoss->getCurrentState() == BOSS_STATE_MOVE || pBoss->getCurrentState() == BOSS_STATE_NOT_MOVE)
                && checkCollision(pRole->getAttackRect(), pBoss->getBodyRect()))
            {
                pBossToAttack = pBoss;
            }
        }
        if (!pBossToAttack && !GameContext::getInstance().getAICanAttack())
        {
            pRole->notReadyToAttack();
        }
        else
        {
            context.setBossCanAttack(pBossToAttack);
            pRole->readyToAttack();
        }
    }
}

void GameLogic::dealCollsionRoleAndAI()
{
    GameContext& context = GameContext::getInstance();
    GameContext::AIArray& aiArray = context.getAIArray();
    Role* pRole = context.getRole();
    if (pRole->getCurrentState() != ROLE_STATE_PRE_CLIMB && pRole->getCurrentState() != ROLE_STATE_CLIMB && pRole->getCurrentState() != ROLE_STATE_DEAD)
    {
        for (int i = 0; i < aiArray.size(); ++i)
        {
            AI* pAI = aiArray.at(i);
            if (pAI->getCurrentState() != AI_STATE_ATTACK  && pAI->getCurrentState() != AI_STATE_DEAD && pAI->getCurrentState() != AI_STATE_REVIVAL && checkCollision(pAI->getAttackRect(), pRole->getBodyRect()))
            {
                pAI->attack();
                pRole->dead();
            }
        }
        AI* pAIToAttack = 0;
        for (int i = 0; i < aiArray.size(); ++i)
        {
            AI* pAI = aiArray.at(i);
            if (pAI->canBeAttack() && pAI->isAttacked(pRole->getAttackRect()))
            {
                pAIToAttack = pAI;
            }
        }
        if (!pAIToAttack && ! GameContext::getInstance().getBossCanAttack())
        {
            pRole->notReadyToAttack();
        }
        else
        {
            context.setAICanAttack(pAIToAttack);
            pRole->readyToAttack();
        }
    }
    else
    {
        pRole->notReadyToAttack();
    }
}

void GameLogic::dealCollisionRoleAndLadder()
{
    GameContext& context = GameContext::getInstance();
    GameContext::SceneObjectArray& ladderArray = GameContext::getInstance().getLadderArray();
    if (context.getRole()->getCurrentState() != ROLE_STATE_PRE_CLIMB
        && context.getRole()->getCurrentState() != ROLE_STATE_CLIMB)
    {
        for (int i = 0; i < ladderArray.size(); ++i)
        {
            Ladder* ladder = (Ladder*) ladderArray.at(i);
            bool canClimbUp = checkCollision(context.getRole()->getBodyRect(), ladder->getCollsionRectDown());
            bool canClimbDown = checkCollision(context.getRole()->getBodyRect(), ladder->getCollsionRectUp());
            if (!ladder->isCollisioned() && (canClimbUp || canClimbDown))
            {
                ladder->onCollision();
                if (canClimbUp)
                {
                    observer_.onLadderCanClimb(ladder, true);
                }
                else if (canClimbDown)
                {
                    observer_.onLadderCanClimb(ladder, false);
                }
            }
            if (ladder->isCollisioned() && (!canClimbUp && !canClimbDown))
            {
                ladder->noCollision();
                observer_.onLadderCanNotClimb(ladder);
            }
        }
    }
    else
    {
        for (int i = 0; i < ladderArray.size(); ++i)
        {
            Ladder* ladder = (Ladder*) ladderArray.at(i);
            ladder->noCollision();
            observer_.onLadderCanNotClimb(ladder);
        }
    }
}

void GameLogic::dealCollisionRoleAndWall()
{
    GameContext& context = GameContext::getInstance();
    GameContext::WallArray wallArray = GameContext::getInstance().getWallArray();
    Role* pRole = context.getRole();
    if (pRole->getCurrentState() == ROLE_STATE_MOVE)
    {
        for (int i = 0; i < wallArray.size(); ++i)
        {
            Wall* wall = wallArray.at(i);
            if (checkCollision(wall->getCollisionRect(), pRole->getBodyRect()))
            {
                if (pRole->getBodyRect().getMidX() < wall->getLeftX())
                {
                    pRole->setPosition(Point(wall->getLeftX() - pRole->getBodyRect().size.width, pRole->getBodyRect().getMinY()));
                    pRole->stop();
                }
                else if (pRole->getBodyRect().getMidX() > wall->getRightX())
                {
                    pRole->stop();
                    pRole->setPosition(Point(wall->getRightX(), pRole->getBodyRect().getMinY()));
                }
            }
        }
    }
}

void GameLogic::dealCollisionBombAndAI()
{
    GameContext& context = GameContext::getInstance();
    GameContext::AIArray& aiArray = context.getAIArray();
    Rect bombRect = context.getBombMovedRect();
    bombRect.origin.y += context.getCurrentOffsetY();
    for (int i = 0; i < aiArray.size(); ++i)
    {
        AI* pAI = aiArray.at(i);
        if (pAI->canBeAttack()
            && pAI->getCurrentState() != AI_STATE_DEAD
            && pAI->getCurrentState() != AI_STATE_REVIVAL
            && bombRect.intersectsRect(pAI->getBodyRect()))
        {
            pAI->dead();
        }
    }
}

void GameLogic::dealCollisionRoleAndBox()
{
    GameContext& context = GameContext::getInstance();
    GameContext::BoxArray boxArray = context.getBoxArray();
    Role* pRole = context.getRole();
    if (pRole->getCurrentState() != ROLE_STATE_DEAD)
    {
        for (int i = 0; i < boxArray.size(); ++i)
        {
            Box* box = boxArray.at(i);
            bool isCollision = checkCollision(pRole->getBodyRect(), box->getCollisionRect());
            if (isCollision)
            {
                if (box->getCurrentState() == BOX_STATE_IDLE)
                {
                    observer_.onBoxCanOpen(box);
                    box->dealCollision();
                }
                else if (box->getCurrentState() == BOX_STATE_PICK_UP)
                {
                    if (!box->getMenuItems()->getParent())
                    {
                        observer_.onBoxCanPickUp(box);
                    }
                }
            }
            else if (box->getCurrentState() != BOX_STATE_IDLE && box->getCurrentState() != BOX_STATE_BOMB)
            {
                box->idle();
            }
        }
    }
}

void GameLogic::dealChangeMapOffsetY()
{
    GameContext& context = GameContext::getInstance();
    Rect roleRect = GameContext::getInstance().getRole()->getBodyRect();
    if (roleRect.getMinY() >= context.getUpEdgeForChangeOffsetY() + context.getCurrentOffsetY())
    {
        if (!changeY_)
        {
            changeY_ = true;
            observer_.moveLayerUp();
        }
    }
    else if (roleRect.getMaxY() <= context.getDownEdgeForChangeOffsetY() + context.getCurrentOffsetY())
    {
        if (!changeY_)
        {
            changeY_ = true;
            observer_.moveLayerDown();
        }
    }
}

void GameLogic::checkMapPass()
{
    GameContext& context = GameContext::getInstance();
    if (context.getBossItem())
    {
        GameContext::BoxArray boxArray = context.getBoxArray();
        for (int i = 0; i < boxArray.size(); ++i)
        {
            if (boxArray.at(i)->getCurrentState() != BOX_STATE_BOMB)
            {
                return;
            }
        }
        context.gameVictory();
    }
}

void GameLogic::showShuraEye()
{
    observer_.onBossItemPickUped();
}

void GameLogic::addMapToLayer(cocos2d::Layer *layer)
{
    layer->addChild(GameContext::getInstance().getMap());
    GameContext::getInstance().addSceneObjectsToLayer(layer);
    GameContext::getInstance().addAIsToLayer(layer);
    GameContext::getInstance().addBossToLayer(layer);
    GameContext::getInstance().getRole()->addRoleToLayer(layer);
}

void GameLogic::addBossItem(Boss *boss)
{
    observer_.onBossItemShowed(boss);
}

//void GameLogic::climbLadder(Ladder *ladder)
//{
//    GameContext& context = GameContext::getInstance();
//    if (checkCollision(context.getRole()->getBodyRect(), ladder->getCollsionRectDown()))
//    {
//        context.getRole()->climb(ladder, true);
//    }
//    else if (checkCollision(context.getRole()->getBodyRect(), ladder->getCollsionRectUp()))
//    {
//        context.getRole()->climb(ladder, false);
//    }
//}

void GameLogic::switchToNextMap(float switchDistance, TMXTiledMap* map)
{
    switchDistance_ = switchDistance;
    observer_.onSwitchMap(map);
    GameStatus prevStatus = status_;
    status_ = GAME_STATUS_SWITCH_MAP;
    observer_.onStatusChanged(prevStatus, status_);
}

void GameLogic::showSwitchAnimation()
{
    GameContext::getInstance().getRole()->victory();
    GameStatus prevStatus = status_;
    status_ = GAME_STATUS_VICTORY;
    observer_.onStatusChanged(prevStatus, status_);
    repeat_ = Repeat::create(Animate::create(AnimationCache::getInstance()->getAnimation("bomb_over")), 1);
    CC_SAFE_RETAIN(repeat_);
    sprite_ = Sprite::create();
    sprite_->runAction(repeat_);
    CC_SAFE_RETAIN(sprite_);
    observer_.showVictoryAnimation(sprite_);
    SimpleAudioEngine::getInstance()->playEffect("effect_bomb_over.mp3");
    SimpleAudioEngine::getInstance()->playEffect("effect_victory.mp3");
}

void GameLogic::updateLightAndBomb(unsigned int count)
{
    observer_.updateLightAndBomb(count);
}

bool GameLogic::checkBombMove(const cocos2d::Point &pos)
{
    GameContext& context = GameContext::getInstance();
    if (context.hasBomb()
        && context.getRole()->getCurrentState() != ROLE_STATE_DEAD
        && context.getRole()->getCurrentState() != ROLE_STATE_VICTORY
        && context.getBombInitialRect().containsPoint(pos))
    {
        return true;
    }
    return false;
}

bool GameLogic::onTouchBegan(Layer* layer, Touch *touch, Event *unused_event)
{
    PlayLayer* pLayer = dynamic_cast<PlayLayer*>(layer);
    if (pLayer)
    {
        if (pLayer->getBoundingBox().containsPoint(touch->getLocation()))
        {
            touch_ = true;
            move_ = false;
            Point pos = pLayer->convertToNodeSpace(touch->getLocation());
            if (checkBombMove(pos))
            {
                bombMove_ = true;
                bombMovePosition_ = pos;
            }
        }
    }
    return true;
}

void GameLogic::onTouchMoved(Layer* layer, Touch *touch, Event *unused_event)
{
    PlayLayer* pLayer = dynamic_cast<PlayLayer*>(layer);
    if (pLayer)
    {
        if (pLayer->getBoundingBox().containsPoint(touch->getLocation()))
        {
            touch_ = false;
            move_ = true;
            if (bombMove_)
            {
                Point pos = pLayer->convertToNodeSpace(touch->getLocation());
                Point add = pos - bombMovePosition_;
                bombMovePosition_ = pos;
                Rect rect = GameContext::getInstance().getBombMovedRect();
                rect.origin.x += add.x;
                rect.origin.y += add.y;
                GameContext::getInstance().setBombMovedRect(rect);
                observer_.onBombMoved(add);
            }
        }
    }
}

void GameLogic::onTouchEnded(Layer* layer, Touch *touch, Event *unused_event)
{
    PlayLayer* pLayer = dynamic_cast<PlayLayer*>(layer);
    if (pLayer)
    {
        if (pLayer->getBoundingBox().containsPoint(touch->getLocation()))
        {
            if (touch_)
            {
                touch_ = false;
                Point pos = pLayer->convertToNodeSpace(touch->getLocation());
                Rect rect = GameContext::getInstance().getRole()->getBodyRect();
                pos.x = pos.x < rect.size.width / 2 ? rect.size.width / 2 : pos.x;
                pos.x = pos.x > pLayer->getContentSize().width - rect.size.width / 2 ? (pLayer->getContentSize().width - rect.size.width / 2) : pos.x;
                pos.y = pos.y + GameContext::getInstance().getCurrentOffsetY();
                GameContext::getInstance().getRole()->moveTo(pos);
            }
            if (move_ && bombMove_)
            {
                bombMove_ = false;
                dealCollisionBombAndAI();
                GameContext::getInstance().bombExplode(); 
                observer_.onBombExplode();
                observer_.updateLightAndBomb(GameContext::getInstance().getLightCount());
                SimpleAudioEngine::getInstance()->playEffect("effect_bomb_over.mp3");
            }
        }
    }
}

void GameLogic::onTouchCancelled(Layer* layer, Touch *touch, Event *unused_event)
{
    if (touch_)
    {
        touch_ = false;
    }
}

bool GameLogic::checkCollision(const cocos2d::Rect &rect1, const cocos2d::Rect &rect2)
{
    return rect1.intersectsRect(rect2);
}
