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

USING_NS_CC;

GameContext::GameContext()
{
    
}

GameContext::~GameContext()
{
    
}

bool GameContext::initTiledMap(const char *tmxFile)
{
    pTiledMap_ = TMXTiledMap::create(tmxFile);
    pTiledMap_->ignoreAnchorPointForPosition(false);
    pTiledMap_->setAnchorPoint(Point::ZERO);
    pTiledMap_->setPosition(Point::ZERO);
    TMXObjectGroup* actorGroup = pTiledMap_->getObjectGroup("roles");
    const ValueVector& valueVector = actorGroup->getObjects();
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
            pRole_ = new Role(ActorFactory::getInstance().getActorPropertyByName(name.c_str()), Point(x, y), direction);
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
            AI* ai = new AI(ActorFactory::getInstance().getActorPropertyByName(name.c_str()), Point(x, y), direction, speed, idleDuration, moveDistance);
            aiArray_.push_back(ai);
        }
    }
    
    TMXObjectGroup* collisionGroup = pTiledMap_->getObjectGroup("collision");
    const ValueVector& collsionVector = collisionGroup->getObjects();
    for (int i = 0; i < collsionVector.size(); ++i)
    {
        ValueMap valueMap = collsionVector.at(i).asValueMap();
        ValueMap::iterator it = valueMap.find("type");
        if (it != valueMap.end() && 0 == (*it).second.asString().compare("ladder"))
        {
            float x = (*valueMap.find("x")).second.asFloat();
            float y = (*valueMap.find("y")).second.asFloat();
            unsigned int tag = (*valueMap.find("tag")).second.asInt();
            Ladder* ladder = new Ladder(tag);
            ladder->setPosition(Point(x, y));
            ladderArray_.push_back(ladder);
        }
    }
    
    return true;
}

void GameContext::updateGameContext(float delta)
{
    pRole_->update(delta);
    for (int i = 0; i < aiArray_.size(); ++i)
    {
        aiArray_.at(i)->update(delta);
    }
}

void GameContext::addSceneObjectsToLayer(cocos2d::Layer *layer)
{
    for (int i = 0; i < ladderArray_.size(); ++i)
    {
        ladderArray_.at(i)->addToLayer(layer);
    }
}

void GameContext::addAIsToLayer(cocos2d::Layer *layer)
{
    for (int i = 0; i < aiArray_.size(); ++i)
    {
        aiArray_.at(i)->addAIToLayer(layer);
    }
}

void GameContext::cleanAICanAttack(AI *ai)
{
    if (aiCanAttack_ == ai)
    {
        aiCanAttack_ = 0;
    }
}
