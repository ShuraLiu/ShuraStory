#ifndef __Kong__DeviceResolution__
#define __Kong__DeviceResolution__

#include "cocos2d.h"

struct Resource
{
    cocos2d::CCSize size;
    const char* directory;
    
    Resource()
    : directory(0)
    {
        size.width = 0;
        size.height = 0;
    }
    Resource(const cocos2d::CCSize& s, const char* dir)
    : size(s)
    , directory(dir)
    {
        
    }
};

class DeviceResolution{
public:
    enum Platform{
        UNKNOWN,
        IPHONE,
        IPHONE_HD,
        IPAD,
        IPAD_HD,
        
        ANDROID_MDPI,
        ANDROID_HDPI,
        ANDROID_XHDPI,
    };
    
private:
    static DeviceResolution* s_pResolution_;
    
    Platform platform_;
    Resource designResource_;
    
    DeviceResolution()
    : platform_(UNKNOWN)
    {
    }
    
    void init();
    
public:
    static DeviceResolution* sharedDeviceResolution();
    static void purgeDeviceResolution();
    
    Platform getPlatform() const {return platform_;}
    const Resource& getDesignResource() const{return designResource_;}
    float transformValue(float v);
    float transformParticleValue(float v);
};

#endif /* defined(__Kong__DeviceResolution__) */
