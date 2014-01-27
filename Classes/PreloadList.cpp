//
//  PreLoadList.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#include "PreloadList.h"

USING_NS_CC;

PreloadList::PreloadList() {
	// TODO Auto-generated constructor stub
    
}

PreloadList::~PreloadList() {
	// TODO Auto-generated destructor stub
}

USING_NS_CC;

// the XML parser calls here with all the elements
void PreloadList::startElement(void *ctx, const char *name, const char **attrs)
{
    CC_UNUSED_PARAM(ctx);
    
    if (0 == strcmp("texture", name))
    {
        TextureLoadInfo loadInfo;
        for(int i = 0; attrs[i]; i += 2)
        {
            const char* key = attrs[i];
            const char* value = attrs[i+1];
            if (0 == strcmp("file_name", key))
            {
                loadInfo.fileName.assign(value);
            }
            else if (0 == strcmp("pixel_format", key))
            {
                if (0 == strcmp("RGBA8888", value))
                {
                    loadInfo.pixelFormat = Texture2D::PixelFormat::RGBA8888;
                }
                else if (0 == strcmp("RGBA888", value))
                {
                    loadInfo.pixelFormat = Texture2D::PixelFormat::RGB888;
                }
                else if (0 == strcmp("RGB565", value))
                {
                    loadInfo.pixelFormat = Texture2D::PixelFormat::RGB565;
                }
                else if (0 == strcmp("A8", value))
                {
                    loadInfo.pixelFormat = Texture2D::PixelFormat::A8;
                }
                else if (0 == strcmp("I8", value))
                {
                    loadInfo.pixelFormat = Texture2D::PixelFormat::I8;
                }
                else if (0 == strcmp("AI88", value))
                {
                    loadInfo.pixelFormat = Texture2D::PixelFormat::AI88;
                }
                else if (0 == strcmp("RGBA4444", value))
                {
                    loadInfo.pixelFormat = Texture2D::PixelFormat::RGBA4444;
                }
                else if (0 == strcmp("RGB5A1", value))
                {
                    loadInfo.pixelFormat = Texture2D::PixelFormat::RGB5A1;
                }
                else if (0 == strcmp("PVRTC4", value))
                {
                    loadInfo.pixelFormat = Texture2D::PixelFormat::PVRTC4;
                }
                else if (0 == strcmp("PVRTC2", value))
                {
                    loadInfo.pixelFormat = Texture2D::PixelFormat::PVRTC2;
                }
            }
        }
        textureLoadInfos_.push_back(loadInfo);
    }
    else if (0 == strcmp("sprite_frame", name))
    {
        SpriteFrameLoadInfo loadInfo;
        for (int i = 0; attrs[i]; i += 2)
        {
            const char* key = attrs[i];
            const char* value = attrs[i+1];
            if (0 == strcmp("file_name", key))
            {
                loadInfo.fileName.assign(value);
            }
        }
        spriteFrameLoadInfos_.push_back(loadInfo);
    }
    else if (0 == strcmp("animation", name))
    {
        AnimationLoadInfo loadInfo;
        for (int i = 0; attrs[i]; i += 2)
        {
            const char* key = attrs[i];
            const char* value = attrs[i+1];
            if (0 == strcmp("file_name", key))
            {
                loadInfo.fileName.assign(value);
            }
        }
        animationLoadInfos_.push_back(loadInfo);
    }
    else if (0 == strcmp("font", name))
    {
        FontLoadInfo loadInfo;
        for (int i = 0; attrs[i]; i += 2)
        {
            const char* key = attrs[i];
            const char* value = attrs[i+1];
            if (0 == strcmp("file_name", key))
            {
                loadInfo.fileName.assign(value);
            }
        }
        fontLoadInfos_.push_back(loadInfo);
    }
    else if (0 == strcmp("background_music", name))
    {
        BackgroundMusicLoadInfo loadInfo;
        for (int i = 0; attrs[i]; i += 2)
        {
            const char* key = attrs[i];
            const char* value = attrs[i+1];
            if (0 == strcmp("file_name", key))
            {
                loadInfo.fileName.assign(value);
            }
        }
        backgroundMusicLoadInfos_.push_back(loadInfo);
    }
    else if (0 == strcmp("effect", name))
    {
        EffectLoadInfo loadInfo;
        for (int i = 0; attrs[i]; i += 2)
        {
            const char* key = attrs[i];
            const char* value = attrs[i+1];
            if (0 == strcmp("file_name", key))
            {
                loadInfo.fileName.assign(value);
            }
        }
        effectLoadInfos_.push_back(loadInfo);
    }
    else if (0 == strcmp("particle", name))
    {
        ParticleLoadInfo loadInfo;
        for (int i = 0; attrs[i]; i += 2)
        {
            const char* key = attrs[i];
            const char* value = attrs[i+1];
            if (0 == strcmp("file_name", key))
            {
                loadInfo.fileName.assign(value);
            }
        }
        particleLoadInfos_.push_back(loadInfo);
    }
}

void PreloadList::endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    CC_UNUSED_PARAM(name);
}

void PreloadList::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    CC_UNUSED_PARAM(ch);
    CC_UNUSED_PARAM(len);
}

void PreloadList::parseFile(const char *fileName)
{
    CCAssert(fileName, "xml file name can not be null");
    SAXParser parser;
    
    if (parser.init("UTF-8"))
    {
        parser.setDelegator(this);
        parser.parse(fileName);
    }
}
