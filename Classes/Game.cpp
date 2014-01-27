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
#include "LoadingScene.h"
#include "LoadingSceneController.h"
#include "HomeScene.h"
#include "HomeSceneController.h"
#include "GameOverScene.h"
#include "GameOverSceneController.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

Game::Game()
: running_(false)
, pGameSceneController_(new GameSceneController())
, pLoadingSceneController_(new LoadingSceneController())
, pHomeSceneController_(new HomeSceneController())
, pGameOverSceneController_(new GameOverSceneController())
{
    
}

Game::~Game()
{
	CC_SAFE_RELEASE_NULL(pGameSceneController_);
    CC_SAFE_RELEASE_NULL(pLoadingSceneController_);
    CC_SAFE_RELEASE_NULL(pHomeSceneController_);
    CC_SAFE_RELEASE_NULL(pGameOverSceneController_);
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
    pLoaderLibrary->registerNodeLoader(LoadingSceneLoader::layerClassName(), LoadingSceneLoader::loader());
    pLoaderLibrary->registerNodeLoader(HomeSceneLoader::layerClassName(), HomeSceneLoader::loader());
    pLoaderLibrary->registerNodeLoader(GameOverSceneLoader::layerClassName(), GameOverSceneLoader::loader());
    pLoadingSceneController_->run();
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

void Game::switchActivity(SwitchActivityParam param)
{
    switch (param)
    {
        case LOADING_FINISHED:
            pHomeSceneController_->run();
            break;
        case READY_TO_PLAY:
            pGameSceneController_->run();
            break;
        case GAME_OVER:
            pGameOverSceneController_->run();
            break;
        default:
            break;
    }
}
