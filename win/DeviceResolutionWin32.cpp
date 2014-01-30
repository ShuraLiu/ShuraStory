//
//  DeviceResolutionIOS.mm
//  NinjaParkour
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#include "DeviceResolution.h"

USING_NS_CC;

static const Resource s_iphoneResource = Resource(cocos2d::Size(480, 320),   "resources-iphone");
static const Resource s_iphonehdResource = Resource(cocos2d::Size(960, 640),   "resources-iphonehd");
static const Resource s_ipadResource = Resource(cocos2d::Size(960, 640/*1024, 768*/),  "resources-ipad");
static const Resource s_ipadhdResource = Resource(cocos2d::Size(960, 640/*2048, 1536*/), "resources-ipadhd");
static const Resource s_win32Resource = Resource(cocos2d::Size(960, 640), "resources-win32");

void DeviceResolution::init()
{
    EGLView* pGlView = CCEGLView::getInstance();
    
    std::vector<std::string> searchPaths;
    std::string searchPath;
    
    platform_ = DeviceResolution::WIN_32;
    designResource_ = s_win32Resource;
    searchPaths.push_back(s_win32Resource.directory);
    
    FileUtils* fileUtils = CCFileUtils::getInstance();
    fileUtils->setSearchPaths(searchPaths);

	pGlView->setDesignResolutionSize(960, 640, ResolutionPolicy::FIXED_HEIGHT);
    
    //Director::getInstance()->setContentScaleFactor(designResource_.size.height/CCEGLView::getInstance()->getDesignResolutionSize().height);
}
