//
//  Game.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#include "Game.h"
#include "cocos2d.h"
#include "GameScene.h"
#include "GameSceneController.h"
#include "PreloadList.h"
#include "PlayLayer.h"
#include "ActorFactory.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

Game::Game()
: running_(false)
, pGameSceneController_(new GameSceneController())
{
    
}

Game::~Game()
{
	CC_SAFE_RELEASE_NULL(pGameSceneController_);
    shutdown();
}

void Game::launch()
{
    if (isRunning())
    {
        return;
    }
    running_ = true;
    
    PreloadList::getInstance().parseFile("load.xml");
    ActorFactory::getInstance().parseFile("actor.xml");
    
    NodeLoaderLibrary* pLoaderLibrary = NodeLoaderLibrary::getInstance();
    pLoaderLibrary->registerNodeLoader(GameSceneLoader::layerClassName(), GameSceneLoader::loader());
    pLoaderLibrary->registerNodeLoader(PlayLayerLoader::layerClassName(), PlayLayerLoader::loader());
    pGameSceneController_->run();
}

void Game::shutdown()
{
    if (!isRunning())
    {
        return;
    }
    running_ = false;
    
    Director::getInstance()->popToRootScene();
    Director::getInstance()->popScene();
}

bool Game::isRunning() const
{
	return running_;
}
