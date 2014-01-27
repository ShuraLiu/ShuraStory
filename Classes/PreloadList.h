//
//  PreLoadList.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#ifndef __mygame__PreLoadList__
#define __mygame__PreLoadList__

#include "cocos2d.h"

class PreloadList
: public cocos2d::SAXDelegator
{
public:
    struct TextureLoadInfo{
        std::string fileName;
        cocos2d::CCTexture2D::PixelFormat pixelFormat;
        
        TextureLoadInfo() : pixelFormat(cocos2d::CCTexture2D::PixelFormat::DEFAULT){}
    };
    
    struct SpriteFrameLoadInfo{
        std::string fileName;
    };
    
    struct AnimationLoadInfo{
        std::string fileName;
    };
    
    struct FontLoadInfo{
        std::string fileName;
    };
    
    struct BackgroundMusicLoadInfo{
        std::string fileName;
    };
    
    struct EffectLoadInfo{
        std::string fileName;
    };
    
    struct ParticleLoadInfo{
        std::string fileName;
    };
    
    typedef std::list<TextureLoadInfo> TextureLoadInfoContainer;
    typedef std::list<SpriteFrameLoadInfo> SpriteFrameLoadInfoContainer;
    typedef std::list<AnimationLoadInfo> AnimationLoadInfoContainer;
    typedef std::list<FontLoadInfo> FontLoadInfoContainer;
    typedef std::list<BackgroundMusicLoadInfo> BackgroundMusicLoadInfoContainer;
    typedef std::list<EffectLoadInfo> EffectLoadInfoContainer;
    typedef std::list<ParticleLoadInfo> ParticleLoadInfoContainer;
    
private:
    TextureLoadInfoContainer textureLoadInfos_;
    SpriteFrameLoadInfoContainer spriteFrameLoadInfos_;
    AnimationLoadInfoContainer animationLoadInfos_;
    FontLoadInfoContainer fontLoadInfos_;
    BackgroundMusicLoadInfoContainer backgroundMusicLoadInfos_;
    EffectLoadInfoContainer effectLoadInfos_;
    ParticleLoadInfoContainer particleLoadInfos_;
public:
	static PreloadList& getInstance()
	{
		static PreloadList list;
		return list;
	}
    
public:
    // implement pure virtual methods of CCSAXDelegator
    void startElement(void *ctx, const char *name, const char **attrs);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
    
public:
    void parseFile(const char* fileName);
    
    const TextureLoadInfoContainer& getTextureLoadInfos() const
    {
        return textureLoadInfos_;
    }
    const SpriteFrameLoadInfoContainer& getSpriteFrameLoadInfos() const
    {
        return spriteFrameLoadInfos_;
    }
    const AnimationLoadInfoContainer& getAnimationLoadInfos() const
    {
        return animationLoadInfos_;
    }
    const FontLoadInfoContainer& getFontLoadInfos() const
    {
        return fontLoadInfos_;
    }
    const BackgroundMusicLoadInfoContainer& getBackgroundMusicLoadInfos() const
    {
        return backgroundMusicLoadInfos_;
    }
    const EffectLoadInfoContainer& getEffectLoadInfos() const
    {
        return effectLoadInfos_;
    }
    const ParticleLoadInfoContainer& getParticleLoadInfos() const
    {
        return particleLoadInfos_;
    }
    
private:
	PreloadList();
public:
	virtual ~PreloadList();
};

#endif /* defined(__mygame__PreLoadList__) */
