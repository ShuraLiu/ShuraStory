//
//  SceneController.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#include "SceneController.h"
#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;

using namespace cocosbuilder;

SceneController* SceneController::s_pCurrentController_ = 0;

SceneController::SceneController(const char* filename)
{
	this->fileName_ = filename;
}

SceneController::~SceneController()
{
}

void SceneController::run()
{
	CCBReader reader(NodeLoaderLibrary::getInstance());
	static float s_resolutionScale = 0;
	if (!s_resolutionScale)
	{
		const Size &winSize = EGLView::getInstance()->getFrameSize();
		if (winSize.width > winSize.height)
		{
			s_resolutionScale = winSize.height / 320.0f;
		}
		else
		{
			s_resolutionScale = winSize.width / 320.0f;
		}
	}
	reader.setResolutionScale(s_resolutionScale);
	Scene* pActivity = reader.createSceneWithNodeGraphFromFile(fileName_.c_str());
	Director* pDirector = Director::getInstance();
	if (pDirector->getRunningScene())
	{
		pDirector->replaceScene(pActivity);
	}
	else
	{
		pDirector->runWithScene(pActivity);
	}
	s_pCurrentController_ = this;
}
