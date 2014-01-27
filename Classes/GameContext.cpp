//
//  GameContext.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-22.
//
//

#include "GameContext.h"
#include "config.h"
#include "ActorFactory.h"
#include "Box.h"
#include "GameLogic.h"

USING_NS_CC;

GameContext::GameContext()
{
    resetMapInfo();
}

GameContext::~GameContext()
{
    
}

bool GameContext::initTiledMap(const char *tmxFile)
{
    pTiledMap_ = TMXTiledMap::create(tmxFile);
    CC_SAFE_RETAIN(pTiledMap_);
    pTiledMap_->ignoreAnchorPointForPosition(false);
    pTiledMap_->setAnchorPoint(Point::ZERO);
    pTiledMap_->setPosition(Point::ZERO);
    initMapObjects(pTiledMap_);
    
    return true;
}

void GameContext::initMapObjects(cocos2d::TMXTiledMap *map)
{
    TMXObjectGroup* actorGroup = map->getObjectGroup("roles");
    if (actorGroup)
    {
        const ValueVector& valueVector = actorGroup->getObjects();
        if (!valueVector.empty())
        {
            for (int i = 0; i < valueVector.size(); ++i)
            {
                ValueMap valueMap =  valueVector.at(i).asValueMap();
                ValueMap::iterator it = valueMap.find("type");
                if (it != valueMap.end() && 0 == (*it).second.asString().compare("role"))
                {
                    float x = (*valueMap.find("x")).second.asFloat();
                    float y = (*valueMap.find("y")).second.asFloat();
                    std::string name = (*valueMap.find("name")).second.asString();
                    std::string direction = (*valueMap.find("direction")).second.asString();
                    if (!pRole_)
                    {
                        pRole_ = new Role(ActorFactory::getInstance().getActorPropertyByName(name.c_str()), Point(x, y), direction);
                    }
                    else
                    {
                        pRole_->reset(Point(x, y), direction);
                    }
                }
                else if (0 == (*it).second.asString().compare("ai"))
                {
                    float x = (*valueMap.find("x")).second.asFloat();
                    float y = (*valueMap.find("y")).second.asFloat();
                    std::string name = (*valueMap.find("name")).second.asString();
                    std::string direction = (*valueMap.find("direction")).second.asString();
                    float idleDuration = (*valueMap.find("idleDuration")).second.asFloat();
                    float moveDistance = (*valueMap.find("moveDistance")).second.asFloat();
                    float speed = (*valueMap.find("speed")).second.asFloat();
                    float initialDuration = (*valueMap.find("initialDuration")).second.asFloat();
                    float revivalDuration = (*valueMap.find("revivalDuration")).second.asFloat();
                    bool isGuard = (*valueMap.find("guard")).second.asBool();
                    int logic = (*valueMap.find("logic")).second.asInt();
                    bool bossMove = (*valueMap.find("bossMove")).second.asBool();
                    bool canBeAttack = (*valueMap.find("canBeAttack")).second.asBool();
                    AI* ai = new AI(ActorFactory::getInstance().getActorPropertyByName(name.c_str()), Point(x, y), direction, speed, idleDuration, moveDistance, initialDuration, revivalDuration, isGuard, logic, bossMove, canBeAttack);
                    aiArray_.push_back(ai);
                }
                else if (0 == (*it).second.asString().compare("boss"))
                {
                    float x = (*valueMap.find("x")).second.asFloat();
                    float y = (*valueMap.find("y")).second.asFloat();
                    std::string name = (*valueMap.find("name")).second.asString();
                    std::string direction = (*valueMap.find("direction")).second.asString();
                    float idleDuration = (*valueMap.find("idleDuration")).second.asFloat();
                    float moveDistance = (*valueMap.find("moveDistance")).second.asFloat();
                    float speed = (*valueMap.find("speed")).second.asFloat();
                    float unbeatCount = (*valueMap.find("unbeatCount")).second.asFloat();
                    float revivalDuration = (*valueMap.find("revivalDuration")).second.asFloat();
                    unsigned int beforeMoveCount = (*valueMap.find("beforeMoveCount")).second.asInt();
                    Boss* boss = new Boss(ActorFactory::getInstance().getActorPropertyByName(name.c_str()), Point(x, y), direction, speed, idleDuration, moveDistance, unbeatCount, revivalDuration, beforeMoveCount);
                    bossArray_.push_back(boss);
                }
            }
        }
    }
    
    TMXObjectGroup* collisionGroup = map->getObjectGroup("collision");
    if (collisionGroup)
    {
        const ValueVector& collsionVector = collisionGroup->getObjects();
        if (!collsionVector.empty())
        {
            for (int i = 0; i < collsionVector.size(); ++i)
            {
                ValueMap valueMap = collsionVector.at(i).asValueMap();
                ValueMap::iterator it = valueMap.find("type");
                if (it != valueMap.end() && 0 == (*it).second.asString().compare("ladder"))
                {
                    float x = (*valueMap.find("x")).second.asFloat();
                    float y = (*valueMap.find("y")).second.asFloat();
                    std::string fileName = (*valueMap.find("fileName")).second.asString();
                    Ladder* ladder = new Ladder(fileName.c_str(), Point(x, y));
                    ladderArray_.push_back(ladder);
                }
                else if (0 == (*it).second.asString().compare("wall"))
                {
                    float x = (*valueMap.find("x")).second.asFloat();
                    float y = (*valueMap.find("y")).second.asFloat();
                    float width = (*valueMap.find("width")).second.asFloat();
                    float heigth = (*valueMap.find("height")).second.asFloat();
                    Wall* wall = new Wall();
                    wall->setCollisionRect(Rect(x, y, width, heigth));
                    wallArray_.push_back(wall);
                }
                else if (0 == (*it).second.asString().compare("box"))
                {
                    float x = (*valueMap.find("x")).second.asFloat();
                    float y = (*valueMap.find("y")).second.asFloat();
                    bool bomb = (*valueMap.find("bomb")).second.asBool();
                    bool pass = (*valueMap.find("pass")).second.asBool();
                    bool coin = (*valueMap.find("coin")).second.asBool();
                    Box* box = new  Box(Point(x, y), bomb, pass, coin);
                    boxArray_.push_back(box);
                }
            }
        }
    }
}

void GameContext::updateGameContext(float delta)
{
    pRole_->update(delta);
    for (int i = 0; i < aiArray_.size(); ++i)
    {
        aiArray_.at(i)->update(delta);
    }
    for (int i = 0; i < boxArray_.size(); ++i)
    {
        boxArray_.at(i)->update(delta);
    }
    for (int i = 0; i < bossArray_.size(); ++i)
    {
        bossArray_.at(i)->update(delta);
    }
}

void GameContext::addSceneObjectsToLayer(cocos2d::Layer *layer)
{
    for (int i = 0; i < ladderArray_.size(); ++i)
    {
        ladderArray_.at(i)->addToLayer(layer);
    }
    for (int i = 0; i < boxArray_.size(); ++i)
    {
        boxArray_.at(i)->addToLayer(layer);
    }
}

void GameContext::addAIsToLayer(cocos2d::Layer *layer)
{
    for (int i = 0; i < aiArray_.size(); ++i)
    {
        aiArray_.at(i)->addAIToLayer(layer);
    }
}

void GameContext::addBossToLayer(cocos2d::Layer *layer)
{
    for (int i = 0; i < bossArray_.size(); ++i)
    {
        bossArray_.at(i)->addBossToLayer(layer);
    }
}

void GameContext::cleanAICanAttack(AI *ai)
{
    if (aiCanAttack_ == ai)
    {
        aiCanAttack_ = 0;
    }
}

void GameContext::cleanBossCanAttack(Boss *boss)
{
    if (bossCanAttack_ == boss)
    {
        bossCanAttack_ = 0;
    }
}

void GameContext::gameVictory()
{
    gameLogic_->showSwitchAnimation();
}

void GameContext::goToNextMap()
{
    pTiledMap2_ = TMXTiledMap::create(mapList.front().c_str());
    CC_SAFE_RETAIN(pTiledMap2_);
    pTiledMap2_->ignoreAnchorPointForPosition(false);
    pTiledMap2_->setAnchorPoint(Point::ZERO);
    gameLogic_->switchToNextMap(pTiledMap_->getContentSize().width, pTiledMap2_);
    lightCount = 0;
}

void GameContext::initNextTiledMap()
{
    CC_SAFE_RELEASE_NULL(pTiledMap_);
    pTiledMap_ = pTiledMap2_;
    pTiledMap2_ = 0;
    clear();
    pTiledMap_->setPosition(Point::ZERO);
    initMapObjects(pTiledMap_);
}

void GameContext::clear()
{
    for (int i = 0; i < ladderArray_.size(); ++i)
    {
        Ladder* ladder = (Ladder*)ladderArray_.at(i);
        delete ladder;
    }
    for (int i = 0; i < aiArray_.size(); ++i)
    {
        delete aiArray_.at(i);
    }
    for (int i = 0; i < wallArray_.size(); ++i)
    {
        delete wallArray_.at(i);
    }
    for (int i = 0; i < boxArray_.size(); ++i)
    {
        delete boxArray_.at(i);
    }
    for (int i = 0; i < bossArray_.size(); ++i)
    {
        delete bossArray_.at(i);
    }
    SceneObjectArray().swap(ladderArray_);
    AIArray().swap(aiArray_);
    WallArray().swap(wallArray_);
    BoxArray().swap(boxArray_);
    BossArray().swap(bossArray_);
}

void GameContext::gameOver()
{
    pTiledMap2_ = TMXTiledMap::create(mapList.front().c_str());
    CC_SAFE_RETAIN(pTiledMap2_);
    pTiledMap2_->ignoreAnchorPointForPosition(false);
    pTiledMap2_->setAnchorPoint(Point::ZERO);
    gameLogic_->switchToNextMap(pTiledMap_->getContentSize().width, pTiledMap2_);
}

void GameContext::addKillCount(unsigned int add)
{
    lightCount += add;
    gameLogic_->updateLightAndBomb(lightCount);
}

bool GameContext::hasBomb()
{
    return lightCount >=4;
}

void GameContext::bombExplode()
{
    bombMovedRect = bombInitialRect;
    lightCount -= 4;
}

void GameContext::killBossGuard(unsigned int count)
{
    for (int i = 0; i < bossArray_.size(); ++i)
    {
        bossArray_.at(i)->subShield(count);
    }
}

bool GameContext::allMapFinished()
{
    mapList.pop_front();
    if (mapList.empty())
    {
        return true;
    }
    return false;
}

void GameContext::resetMapInfo()
{
    MapList().swap(mapList);
    mapList.push_back(std::string("game_0.tmx"));
    mapList.push_back(std::string("game_1.tmx"));
    mapList.push_back(std::string("game_2.tmx"));
    mapList.push_back(std::string("game_3.tmx"));
    mapList.push_back(std::string("game_4.tmx"));
}

void GameContext::addBomb(unsigned int count)
{
    lightCount += count * 4;
    gameLogic_-> updateLightAndBomb(lightCount);
}

void GameContext::subBossBeforeMoveCount(unsigned int count)
{
    for (int i = 0; i < bossArray_.size(); ++i)
    {
        bossArray_.at(i)->subBeforeMove(count);
    }
}

void GameContext::showBossItem()
{
    Boss* boss = bossCanAttack_;
    gameLogic_->addBossItem(boss);
}

void GameContext::pickUpBossItem()
{
    bossItem_ = true;
    gameLogic_->showShuraEye();
    
}

const char* GameContext::getCurrentMapName()
{
    return mapList.front().c_str();
}

void GameContext::initData()
{
    setOffsetYChangeOnce(12 * 32);
    setUpEdgeForChangeOffsetY(32 * 19);
    setDownEdgeForChangeOffsetY(0);
    setCurrentOffsetY(0);
    setBossItem(false);
    setLightCount(0);
    aiCanAttack_ = 0;
    bossCanAttack_ = 0;
}
