//
//  DeviceResolutionIOS.mm
//  NinjaParkour
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#import "DeviceResolution.h"

USING_NS_CC;

static const Resource s_iphoneResource = Resource(cocos2d::Size(480, 320),   "resources-iphone");
static const Resource s_iphonehdResource = Resource(cocos2d::Size(960, 640),   "resources-iphonehd");
static const Resource s_ipadResource = Resource(cocos2d::Size(960, 640/*1024, 768*/),  "resources-ipad");
static const Resource s_ipadhdResource = Resource(cocos2d::Size(960, 640/*2048, 1536*/), "resources-ipadhd");

void DeviceResolution::init()
{
    EGLView* pGlView = CCEGLView::getInstance();
    
    std::vector<std::string> searchPaths;
    std::string searchPath;
    
    cocos2d::Size frameSize = pGlView->getFrameSize();
    if (frameSize.height > s_ipadResource.size.height)
    {
        platform_ = DeviceResolution::IPAD_HD;
        designResource_ = s_iphonehdResource;
        searchPaths.push_back(s_ipadhdResource.directory);
    }
    else if (frameSize.height > s_iphonehdResource.size.height)
    {
        platform_ = DeviceResolution::IPAD;
        designResource_ = s_ipadResource;
        searchPaths.push_back(s_ipadResource.directory);
    }
    else if (frameSize.height > s_iphoneResource.size.height)
    {
        platform_ = DeviceResolution::IPHONE_HD;
        designResource_ = s_iphonehdResource;
        searchPaths.push_back(s_iphonehdResource.directory);
    }
    else
    {
        platform_ = DeviceResolution::IPHONE;
        designResource_ = s_iphoneResource;
        searchPaths.push_back(s_iphoneResource.directory);
    }
    
    FileUtils* fileUtils = CCFileUtils::getInstance();
    fileUtils->setSearchPaths(searchPaths);
    
    Director::getInstance()->setContentScaleFactor(designResource_.size.height/CCEGLView::getInstance()->getDesignResolutionSize().height);
}
