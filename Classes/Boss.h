//
//  Boss.h
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#ifndef __ShuraStory__Boss__
#define __ShuraStory__Boss__

#include "cocos2d.h"
#include "Actor.h"

class BaseState;
class ActorProperty;

enum BOSS_STATE
{
    BOSS_STATE_NONE,
    BOSS_STATE_NOT_MOVE,
    BOSS_STATE_IDLE,
    BOSS_STATE_MOVE,
    BOSS_STATE_ATTACK,
    BOSS_STATE_DEAD,
    BOSS_STATE_REVIVAL,
};

class Boss
: public Actor
{
    typedef std::vector<cocos2d::Action*> ActionArray;
    
public:
    void setPosition(const cocos2d::Point& pos);
    void addBossToLayer(cocos2d::Layer* layer);
    void stop();
    void attack();
    void dead();
    void reset();
    void deadByBomb();
    void waitForRevival();
    void subShield(unsigned int count);
    void subBeforeMove(unsigned int count);
    
public:
    enum Action
    {
        ACTION_IDLE = 0,
        ACTION_MOVE,
        ACTION_ATTACK,
        ACTION_DEAD,
        ACTION_NOT_BEAT,
        ACTION_COUNT,
    };
    
public:
    void init(const cocos2d::Point& initialPosition, const std::string& direction);
    void update(float delta);
    
public:
    Boss(ActorProperty* property, const cocos2d::Point& initialPosition, const std::string& direction, float speed, float idleDuration, float moveDistance, float unbeatCount, float revivalDuration, unsigned int beforeMoveCount);
    virtual ~Boss();
    
    cocos2d::Sprite* getBossSprite()
    {
        return pBossSprite_;
    }
    
    float getSpeedMove() const
    {
        return speedMove_;
    }
    
    cocos2d::Rect getBodyRect()
    {
        return getCollisionBodyRect();
    }
    
    cocos2d::Rect getCollisionBodyRect();
    
    const ActionArray& getActions()
    {
        return actions_;
    }
    
    BOSS_STATE getCurrentState() const
    {
        return mState_;
    }
    
    BOSS_STATE getPrevState() const
    {
        return mPrevState_;
    }
    
    cocos2d::Rect getAttackRect();
    
    bool canBeAttack()
    {
        return unbeatCount_ == 0;
    }
    
    cocos2d::Menu* getMenuPass()
    {
        return pMenuItem_;
    }
    
private:
    bool changeState(BOSS_STATE state);
    void switchDirection(Direction direction);
    void doAutoLogic(float delta);
    void initMenu();
    void onMenuPass(cocos2d::Object* obj);
    
private:
    
    CC_SYNTHESIZE(float, speedMove_, Speed);
    CC_SYNTHESIZE(float, idleDuration_, IdleDuration);
    CC_SYNTHESIZE(float, autoMoveDistance_, MoveDistance);
    CC_SYNTHESIZE(float, unbeatCount_, UnBeatCount);
    CC_SYNTHESIZE(float, revivalDuration_, RevivalDuration);
    CC_SYNTHESIZE(float, currentIdleDuration_, CurrentIdleDuration);
    CC_SYNTHESIZE(unsigned int, beforeMoveCount_, BeforeMoveCount);
    BaseState* pBossStateIdle_;
    BaseState* pBossStateMove_;
    BaseState* pBossStateAttack_;
    BaseState* pBossStateDead_;
//    BaseState* pBossStateUnbeatable_;
    BaseState* pBossStateRevival_;
    BaseState* pBossStateNotMove_;
    CC_SYNTHESIZE(BaseState*, pBossStateCurrent_, BossStateCurrent);
    CC_SYNTHESIZE(float, currentRevivalDuration_, CurrentRevivalDuration);
    CC_SYNTHESIZE(float, currentMoveDistance_, CurrentMoveDistance);
    
    BOSS_STATE mState_;
    BOSS_STATE mPrevState_;
    
    ActionArray actions_;
    
    cocos2d::Sprite* pBossSprite_;
    
    float currentInitialDuration_;
    bool autoLogic_;
    ActorProperty* property_;
    
    cocos2d::Point initialPosition_;
    cocos2d::Point autoMoveEndPosition_;
    cocos2d::Point currentTargetPosition_;
    float totalRevivalDuration_;
    
    cocos2d::Menu* pMenuItem_;
};

#endif /* defined(__ShuraStory__Boss__) */
