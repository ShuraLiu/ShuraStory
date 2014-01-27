/*
 * LoadLogic.cpp
 *
 *  Created on: 2013-12-10
 *      Author: shura
 */

#include "LoadLogic.h"
#include "SimpleAudioEngine.h"
#include "Game.h"

USING_NS_CC;

using namespace CocosDenshion;

LoadLogic::LoadLogic(IObserver& observer, PreloadList& loadList)
: observer_(observer)
, loadList_(loadList)
, status_(LOAD_STATUS_NONE)
, textureLoadInfos_(loadList.getTextureLoadInfos())
, spriteFrameLoadInfos_(loadList.getSpriteFrameLoadInfos())
, animationLoadInfos_(loadList.getAnimationLoadInfos())
, fontLoadInfos_(loadList.getFontLoadInfos())
, backgroundMusicLoadInfos_(loadList.getBackgroundMusicLoadInfos())
, effectLoadInfos_(loadList.getEffectLoadInfos())
, particleLoadInfos_(loadList.getParticleLoadInfos())
, loadingTexture_(false)
, loadingSpriteFrame_(false)
, loadingAnimation_(false)
, loadingFont_(false)
, loadingBackgroundMusic_(false)
, loadingEffect_(false)
, loadingParticle_(false)
{
    loadingTextureInfoIter_ = textureLoadInfos_.end();
    loadingSpriteFrameInfoIter_ = spriteFrameLoadInfos_.end();
    loadingAnimationInfoIter_ = animationLoadInfos_.end();
    loadingFontInfoIter_ = fontLoadInfos_.end();
    loadingBackgroundMusicInfoIter_ = backgroundMusicLoadInfos_.end();
    loadingEffectInfoIter_ = effectLoadInfos_.end();
    loadingParticleInfoIter_ = particleLoadInfos_.end();
}

LoadLogic::~LoadLogic()
{

}

void LoadLogic::onLoadingFrame(float delta)
{
    switch (status_)
    {
        case LOAD_STATUS_NONE:
        {
//        	CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
//        	CCTextureCache::sharedTextureCache()->addImage("ui_0.pvr.ccz");
//        	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui_0.plist");
            status_ = LOAD_STATUS_LOADING_LOAD_BACKGROUND;
            observer_.onStatusChanged(LOAD_STATUS_NONE, status_);
        }
            break;
        case LOAD_STATUS_LOADING_LOAD_BACKGROUND:
	   {
		   status_ = LOAD_STATUS_LOADING_TEXTURE;
		   observer_.onStatusChanged(LOAD_STATUS_LOADING_LOAD_BACKGROUND, status_);
	   }
            break;
        case LOAD_STATUS_LOADING_TEXTURE:
		{
			if (textureLoadInfos_.end() != loadingTextureInfoIter_)
			{
				Texture2D::setDefaultAlphaPixelFormat((*loadingTextureInfoIter_).pixelFormat);
                Director::getInstance()->getTextureCache()->addImage((*loadingTextureInfoIter_).fileName.data());
				++loadingTextureInfoIter_;
			}
			else
			{
				Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
				status_ = LOAD_STATUS_LOADING_SPRITE_FRAME;
				loadingSpriteFrameInfoIter_ = spriteFrameLoadInfos_.begin();
				observer_.onStatusChanged(LOAD_STATUS_LOADING_TEXTURE, status_);
			}
		}
            break;
        case LOAD_STATUS_LOADING_SPRITE_FRAME:
            if (spriteFrameLoadInfos_.end() != loadingSpriteFrameInfoIter_)
            {
                SpriteFrameCache::getInstance()->addSpriteFramesWithFile((*loadingSpriteFrameInfoIter_).fileName.data());
                ++loadingSpriteFrameInfoIter_;
            }
            else
            {
                status_ = LOAD_STATUS_LOADING_ANIMATION;
                loadingAnimationInfoIter_ = animationLoadInfos_.begin();
                observer_.onStatusChanged(LOAD_STATUS_LOADING_SPRITE_FRAME, status_);
            }
            break;
        case LOAD_STATUS_LOADING_ANIMATION:
            if (animationLoadInfos_.end() != loadingAnimationInfoIter_)
            {
                AnimationCache::getInstance()->addAnimationsWithFile((*loadingAnimationInfoIter_).fileName.data());
                ++loadingAnimationInfoIter_;
            }
            else
            {
                status_ = LOAD_STATUS_LOADING_FONT;
                loadingFontInfoIter_ = fontLoadInfos_.begin();
                observer_.onStatusChanged(LOAD_STATUS_LOADING_ANIMATION, status_);
            }
            break;
        case LOAD_STATUS_LOADING_FONT:
            if (fontLoadInfos_.end() != loadingFontInfoIter_)
            {
                FNTConfigLoadFile((*loadingFontInfoIter_).fileName.data());
                ++loadingFontInfoIter_;
            }
            else
            {
                status_ = LOAD_STATUS_LOADING_BACKGROUND_MUSIC;
                loadingBackgroundMusicInfoIter_ = backgroundMusicLoadInfos_.begin();
                observer_.onStatusChanged(LOAD_STATUS_LOADING_FONT, status_);
            }
            break;
        case LOAD_STATUS_LOADING_BACKGROUND_MUSIC:
            if (backgroundMusicLoadInfos_.end() != loadingBackgroundMusicInfoIter_)
            {
                ++loadingBackgroundMusicInfoIter_;
            }
            else
            {
                status_ = LOAD_STATUS_LOADING_EFFECT;
                loadingEffectInfoIter_ = effectLoadInfos_.begin();
                observer_.onStatusChanged(LOAD_STATUS_LOADING_BACKGROUND_MUSIC, status_);
            }
            break;
        case LOAD_STATUS_LOADING_EFFECT:
            if (effectLoadInfos_.end() != loadingEffectInfoIter_)
            {
                SimpleAudioEngine::getInstance()->preloadEffect((*loadingEffectInfoIter_).fileName.data());
                ++loadingEffectInfoIter_;
            }
            else
            {
                status_ = LOAD_STATUS_LOADING_PARTICLE;
                loadingParticleInfoIter_ = particleLoadInfos_.begin();
                observer_.onStatusChanged(LOAD_STATUS_LOADING_EFFECT, status_);
            }
            break;
        case LOAD_STATUS_LOADING_PARTICLE:
            if (particleLoadInfos_.end() != loadingParticleInfoIter_)
            {
                CCParticleSystemQuad::create((*loadingParticleInfoIter_).fileName.data());
                ++loadingParticleInfoIter_;
            }
            else
            {
                status_ = LOAD_STATUS_SUCCESSFULLY_FINISHED;
                observer_.onStatusChanged(LOAD_STATUS_LOADING_PARTICLE, status_);
            }
            break;
        case LOAD_STATUS_SUCCESSFULLY_FINISHED:
        {
//        	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui_0.plist");
//        	CCTextureCache::sharedTextureCache()->removeTextureForKey("ui_0.pvr.ccz");
            SimpleAudioEngine::getInstance()->playBackgroundMusic("music_background.mp3", true);
            Game::getInstance().switchActivity(LOADING_FINISHED);
        }
            break;
        case LOAD_STATUS_ERROR:
            break;
    }
}

