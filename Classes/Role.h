//
//  Role.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#ifndef __mygame__Role__
#define __mygame__Role__

#include "cocos2d.h"
#include "Actor.h"

class BaseState;
class Ladder;
class ActorProperty;

enum ROLE_STATE
{
    ROLE_STATE_NONE,
    ROLE_STATE_IDLE,
    ROLE_STATE_MOVE,
    ROLE_STATE_PRE_CLIMB,
    ROLE_STATE_CLIMB,
    ROLE_STATE_ATTACK,
    ROLE_STATE_ATTACKED,
    ROLE_STATE_DEAD,
    ROLE_STATE_VICTORY,
};

class Role
: public Actor
{
    typedef std::vector<cocos2d::Action*> ActionArray;
    
public:
    void setPosition(const cocos2d::Point& pos);
    void addRoleToLayer(cocos2d::Layer* layer);
    void moveTo(const cocos2d::Point& pos);
    void climb(Ladder* ladder, bool isClimbUp);
    void stop();
    void attack();
    void readyToAttack();
    void notReadyToAttack();
    void dead();
    void victory();
    
public:
    enum Action
    {
        ACTION_IDLE = 0,
        ACTION_MOVE,
        ACTION_CLIMB,
        ACTION_ATTACK,
        ACTION_DEAD,
        ACTION_VICTORY,
        ACTION_COUNT,
    };
    
public:
    void init(const cocos2d::Point& initialPosition, const std::string& direction);
    void update(float delta);
    void runAction(Action action);
    void reset(const cocos2d::Point& initialPosition, const std::string& direction);

public:
    Role(ActorProperty* property, const cocos2d::Point& initialPosition, const std::string& direction);
    virtual ~Role();
    
    cocos2d::Sprite* getRoleSprite()
    {
        return pRoleSprite_;
    }
    
    float getSpeedMove() const
    {
        return speedMove_;
    }
    
    float getSpeedClimb() const
    {
        return speedClimb_;
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
    
    BaseState* getRoleStateIdle() const
    {
        return pRoleStateIdle_;
    }
    
    BaseState* getRoleStateMove() const
    {
        return pRoleStateMove_;
    }
    
    BaseState* getRoleStateAttack() const
    {
        return pRoleStateAttack_;
    }
    
    BaseState* getRoleStateAttacked() const
    {
        return pRoleStateAttacked_;
    }
    
    BaseState* getRoleStateDead() const
    {
        return pRoleStateDead_;
    }
    
    bool isClimbing() const
    {
        return isClimbing_;
    }
    
    ROLE_STATE getCurrentState() const
    {
        return mState_;
    }
    
    ROLE_STATE getPrevState() const
    {
        return mPrevState_;
    }
    
    cocos2d::Rect getAttackRect();
    
    bool victoryAnimationFinished() const;
    
private:
    bool changeState(ROLE_STATE state);
    void switchDirection(Direction direction);
    
    void onMenuAttack(cocos2d::Object* obj);
    
private:
    ActorProperty* property_;
    BaseState* pRoleStateIdle_;
    BaseState* pRoleStateMove_;
    BaseState* pRoleStatePreClimb_;
    BaseState* pRoleStateClimb_;
    BaseState* pRoleStateAttack_;
    BaseState* pRoleStateAttacked_;
    BaseState* pRoleStateDead_;
    BaseState* pRoleStateVictory_;
    BaseState* pCurrentState_;
    
    ROLE_STATE mState_;
    ROLE_STATE mPrevState_;
    
    ActionArray actions_;
    
    cocos2d::Sprite* pRoleSprite_;
    float speedMove_;
    float speedClimb_;
    
    bool isClimbing_;
    cocos2d::Point positionToMove_;
    cocos2d::Point positionBeforeClimb_;
    cocos2d::Point positionAfterClimb_;
    
    Action currentAction_;
};

#endif /* defined(__mygame__Role__) */
