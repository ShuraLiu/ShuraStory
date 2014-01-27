//
//  AI.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#ifndef __mygame__AI__
#define __mygame__AI__

#include "cocos2d.h"
#include "Actor.h"

const static int AI_ACTION_DEAD_TAG = 201;

class BaseState;
class ActorProperty;
class AIAutoLogic;

enum AI_STATE
{
    AI_STATE_NONE,
    AI_STATE_INITIAL,
    AI_STATE_IDLE,
    AI_STATE_MOVE,
    AI_STATE_ATTACK,
    AI_STATE_DEAD,
    AI_STATE_REVIVAL,
};

class AI
: public Actor
{
    typedef std::vector<cocos2d::Action*> ActionArray;
    
public:
    void setPosition(const cocos2d::Point& pos);
    void addAIToLayer(cocos2d::Layer* layer);
    void stop();
    void attack();
    void dead();
    void waitForRevival();
    void reset();
    void deadByBomb();
    bool isGuard();
    void move();
    
public:
    enum Action
    {
        ACTION_IDLE = 0,
        ACTION_MOVE,
        ACTION_ATTACK,
        ACTION_ATTACKED,
        ACTION_DEAD,
        ACTION_COUNT,
    };
    
public:
    void init(const cocos2d::Point& initialPosition, const std::string& direction, int logic);
    void update(float delta);
    bool changeState(AI_STATE state);
    
public:
    AI(ActorProperty* property, const cocos2d::Point& initialPosition, const std::string& direction, float speed, float idleDuration, float moveDistance, float initialDuration, float revivalDuration, bool guard, int logic, bool bossMove, bool canBeAttack);
    virtual ~AI();
    
    cocos2d::Sprite* getAISprite()
    {
        return pAISprite_;
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
    
    AI_STATE getCurrentState() const
    {
        return mState_;
    }
    
    AI_STATE getPrevState() const
    {
        return mPrevState_;
    }
    
    cocos2d::Rect getAttackRect();
    
    bool canBeAttack() const
    {
        return canBeAttack_;
    }
    
public:
    void switchDirection(Direction direction);
    void doAutoLogic(float delta);
    
private:
    
    CC_SYNTHESIZE(float, speedMove_, Speed);
    CC_SYNTHESIZE(float, idleDuration_, IdleDuration);
    CC_SYNTHESIZE(float, autoMoveDistance_, MoveDistance);
    CC_SYNTHESIZE(float, initialDuration_, InitialDuration);
    CC_SYNTHESIZE(float, revivalDuration_, RevivalDuration);
    CC_SYNTHESIZE(float, currentIdleDuration_, CurrentIdleDuration);
    CC_SYNTHESIZE(float, guard_, Guard);
    CC_SYNTHESIZE(float, bossMove_, BossMove);
    BaseState* pAIStateIdle_;
    BaseState* pAIStateMove_;
    BaseState* pAIStateAttack_;
    BaseState* pAIStateDead_;
    BaseState* pAIStateInitial_;
    BaseState* pAIStateRevival_;
    CC_SYNTHESIZE(BaseState*, pAIStateCurrent_, AIStateCurrent);
    CC_SYNTHESIZE(float, currentRevivalDuration_, CurrentRevivalDuration);
    CC_SYNTHESIZE(float, currentMoveDistance_, CurrentMoveDistance);
    
    AI_STATE mState_;
    AI_STATE mPrevState_;
    
    ActionArray actions_;
    
    cocos2d::Sprite* pAISprite_;
    
//    float currentInitialDuration_;
    CC_SYNTHESIZE(float, currentInitialDuration_, CurrentInitialDuration);
    bool autoLogic_;
    ActorProperty* property_;
    
//    cocos2d::Point initialPosition_;
    CC_SYNTHESIZE(cocos2d::Point, initialPosition_, InitialPosition);
//    cocos2d::Point autoMoveEndPosition_;
    CC_SYNTHESIZE(cocos2d::Point, autoMoveEndPosition_, AutoMoveEndPosition);
//    cocos2d::Point currentTargetPosition_;
    CC_SYNTHESIZE(cocos2d::Point, currentTargetPosition_, CurrentTargetPosition);
//    float totalRevivalDuration_;
    CC_SYNTHESIZE(float, totalRevivalDuration_, TotalRevivalDuration);
    
    bool canBeAttack_;
    
    AIAutoLogic* pAutoLogic_;
};

#endif /* defined(__mygame__AI__) */
