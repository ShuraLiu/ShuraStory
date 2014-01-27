/*
 * LoadLogic.h
 *
 *  Created on: 2013-12-10
 *      Author: shura
 */

#ifndef LOADLOGIC_H_
#define LOADLOGIC_H_

#include "PreloadList.h"
#include "cocos2d.h"

class LoadLogic
: public cocos2d::CCObject
{

public:
    enum LoadStatus{
        LOAD_STATUS_NONE,
        LOAD_STATUS_LOADING_LOAD_BACKGROUND,
        LOAD_STATUS_LOADING_TEXTURE,
        LOAD_STATUS_LOADING_SPRITE_FRAME,
        LOAD_STATUS_LOADING_ANIMATION,
        LOAD_STATUS_LOADING_FONT,
        LOAD_STATUS_LOADING_BACKGROUND_MUSIC,
        LOAD_STATUS_LOADING_EFFECT,
        LOAD_STATUS_LOADING_PARTICLE,
        LOAD_STATUS_SUCCESSFULLY_FINISHED,
        LOAD_STATUS_ERROR
    };

    class IObserver{
    public:
        virtual ~IObserver(){}

    public:
        virtual void onStatusChanged(LoadStatus prevStatus, LoadStatus status) = 0;
    };

private:
    IObserver& observer_;
    PreloadList& loadList_;

    LoadStatus status_;

    const PreloadList::TextureLoadInfoContainer& textureLoadInfos_;
    const PreloadList::SpriteFrameLoadInfoContainer& spriteFrameLoadInfos_;
    const PreloadList::AnimationLoadInfoContainer& animationLoadInfos_;
    const PreloadList::FontLoadInfoContainer& fontLoadInfos_;
    const PreloadList::BackgroundMusicLoadInfoContainer& backgroundMusicLoadInfos_;
    const PreloadList::EffectLoadInfoContainer& effectLoadInfos_;
    const PreloadList::ParticleLoadInfoContainer& particleLoadInfos_;

    PreloadList::TextureLoadInfoContainer::const_iterator loadingTextureInfoIter_;
    PreloadList::SpriteFrameLoadInfoContainer::const_iterator loadingSpriteFrameInfoIter_;
    PreloadList::AnimationLoadInfoContainer::const_iterator loadingAnimationInfoIter_;
    PreloadList::FontLoadInfoContainer::const_iterator loadingFontInfoIter_;
    PreloadList::BackgroundMusicLoadInfoContainer::const_iterator loadingBackgroundMusicInfoIter_;
    PreloadList::EffectLoadInfoContainer::const_iterator loadingEffectInfoIter_;
    PreloadList::ParticleLoadInfoContainer::const_iterator loadingParticleInfoIter_;
    bool loadingTexture_;
    bool loadingSpriteFrame_;
    bool loadingAnimation_;
    bool loadingFont_;
    bool loadingBackgroundMusic_;
    bool loadingEffect_;
    bool loadingParticle_;

public:
    // IObserver's life cycle must be longer than LoadLogic
    explicit LoadLogic(IObserver& observer, PreloadList& loadList);
    ~LoadLogic();

public:
    void onLoadingFrame(float delta);
};

#endif /* LOADLOGIC_H_ */
