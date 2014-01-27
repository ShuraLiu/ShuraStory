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

class RoleState;
class ActorProperty;

enum AI_STATE
{
    AI_STATE_NONE,
    AI_STATE_IDLE,
    AI_STATE_MOVE,
    AI_STATE_ATTACK,
    AI_STATE_ATTACKED,
    AI_STATE_DEAD,
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
    void init(const cocos2d::Point& initialPosition, const std::string& direction);
    void update(float delta);
    
public:
    AI(ActorProperty* property, const cocos2d::Point& initialPosition, const std::string& direction, float speed, float idleDuration, float moveDistance);
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
    
private:
    bool changeState(AI_STATE state);
    void switchDirection(Direction direction);
    void doAutoLogic(float delta);
    
private:
    
    CC_SYNTHESIZE(float, speedMove_, Speed);
    CC_SYNTHESIZE(float, idleDuration_, IdleDuration);
    CC_SYNTHESIZE(float, autoMoveDistance_, MoveDistance);
    RoleState* pAIStateIdle_;
    RoleState* pAIStateMove_;
    RoleState* pAIStateAttack_;
    RoleState* pAIStateAttacked_;
    RoleState* pAIStateDead_;
    
    AI_STATE mState_;
    AI_STATE mPrevState_;
    
    ActionArray actions_;
    
    cocos2d::Sprite* pAISprite_;
    
    float currentIdleDuration_;
    float currentMoveDistance_;
    bool autoLogic_;
    ActorProperty* property_;
    
    cocos2d::Point initialPosition_;
    cocos2d::Point autoMoveEndPosition_;
    cocos2d::Point currentTargetPosition_;
};

#endif /* defined(__mygame__AI__) */
