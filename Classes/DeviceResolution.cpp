//
//  DeviceResolution.cpp
//  NinjaParkour
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#include "DeviceResolution.h"

using namespace cocos2d;

DeviceResolution* DeviceResolution::s_pResolution_ = 0;

DeviceResolution* DeviceResolution::sharedDeviceResolution()
{
    if (!s_pResolution_)
    {
        s_pResolution_ = new DeviceResolution();
        s_pResolution_->init();
    }
    return s_pResolution_;
}

void DeviceResolution::purgeDeviceResolution()
{
    if (s_pResolution_)
    {
        delete s_pResolution_;
        s_pResolution_ = 0;
    }
}

float DeviceResolution::transformValue(float v)
{
    return CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width*v / designResource_.size.width;
}

float DeviceResolution::transformParticleValue(float v)
{
    return CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width*v / 320;
}
