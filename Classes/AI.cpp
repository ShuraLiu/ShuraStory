//
//  AI.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#include "AI.h"
#include "config.h"
#include "AIStateIdle.h"
#include "AIStateMove.h"
#include "AIStateAttack.h"
#include "AIStateDead.h"
#include "AIStateInitial.h"
#include "AIStateRevival.h"
#include "Utils.h"
#include "ActorProperty.h"
#include "GameContext.h"
#include "AIAutoLogic0.h"
#include "AIAutoLogic.h"

USING_NS_CC;

AI::AI(ActorProperty* property, const cocos2d::Point& initialPosition, const std::string& direction, float speed, float idleDuration, float moveDistance, float initialDuration, float revivalDuration, bool guard, int logic, bool bossMove, bool canBeAttack)
: pAIStateIdle_(new AIStateIdle(this))
, pAIStateMove_(new AIStateMove(this))
, pAIStateAttack_(new AIStateAttack(this))
, pAIStateDead_(new AIStateDead(this))
, pAIStateInitial_(new AIStateInitial(this))
, pAIStateRevival_(new AIStateRevival(this))
, pAIStateCurrent_(0)
, speedMove_(speed)
, idleDuration_(idleDuration)
, autoMoveDistance_(moveDistance)
, initialDuration_(initialDuration)
, guard_(guard)
, mState_(AI_STATE_NONE)
, mPrevState_(AI_STATE_NONE)
, autoLogic_(true)
, currentIdleDuration_(0)
, currentMoveDistance_(0)
, currentInitialDuration_(0)
, currentRevivalDuration_(0)
, totalRevivalDuration_(revivalDuration)
, bossMove_(bossMove)
, canBeAttack_(canBeAttack)
, property_(property)
{
    init(initialPosition, direction, logic);
}

AI::~AI()
{
    delete pAIStateIdle_;
    delete pAIStateMove_;
    delete pAIStateAttack_;
    delete pAIStateDead_;
    delete pAIStateInitial_;
    delete pAIStateRevival_;
    delete pAutoLogic_;
    
    ActionArray::iterator it = actions_.begin();
    ActionArray::iterator end = actions_.end();
    for (; it != end; ++it)
    {
        if ((*it))
        {
            (*it)->release();
        }
    }
}

void AI::init(const cocos2d::Point& initialPosition, const std::string& direction, int logic)
{
    switch (logic) {
        case 0:
            pAutoLogic_ = new AIAutoLogic0(this);
            break;
            
        default:
            break;
    }
    getActorSprite()->setAnchorPoint(Point::ZERO);
    setPosition(initialPosition);
    
    actions_.resize(ACTION_COUNT, 0);
    RepeatForever* move = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(property_->action_move.c_str())));
    actions_.at(ACTION_MOVE) = move;
    CC_SAFE_RETAIN(move);
    RepeatForever* idle = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(property_->action_idle.c_str())));
    actions_.at(ACTION_IDLE) = idle;
    CC_SAFE_RETAIN(idle);
    Animate* attack = Animate::create(AnimationCache::getInstance()->getAnimation(property_->action_attack.c_str()));
    actions_.at(ACTION_ATTACK) = attack;
    CC_SAFE_RETAIN(attack);
    Animate* dead = Animate::create(AnimationCache::getInstance()->getAnimation(property_->action_dead.c_str()));
    actions_.at(ACTION_DEAD) = dead;
    dead->setTag(AI_ACTION_DEAD_TAG);
    CC_SAFE_RETAIN(dead);
    
    if (0 == std::strcmp(direction.c_str(), "left"))
    {
        direction_ = LEFT;
    }
    else
    {
        direction_ = RIGHT;
    }
    initialDirection_ = direction_;
    
    initialPosition_ = getActorSprite()->getPosition();
    float x = (direction_ == LEFT) ? (initialPosition_.x + autoMoveDistance_) : (initialPosition_.x - autoMoveDistance_);
    float y = initialPosition_.y;
    autoMoveEndPosition_ = Point(x, y);
    currentTargetPosition_ = initialPosition_;
    
    if (0 != std::strcmp(direction.c_str(), property_->direction.c_str()))
    {
        getActorSprite()->setFlippedX(true);
    }
    
    if (changeState(AI_STATE_INITIAL))
    {
        pAIStateInitial_->enter();
    }
}

void AI::update(float delta)
{
//    doAutoLogic(delta);
    pAutoLogic_->doAutoLogic(delta);
}

void AI::doAutoLogic(float delta)
{
	Sprite* pAISprite = getActorSprite();
    switch (mState_) {
        case AI_STATE_INITIAL:
        {
            currentInitialDuration_ += delta;
            if (utils::floatGreaterEuqalCompare(currentInitialDuration_, initialDuration_))
            {
                stop();
            }
        }
            break;
        case AI_STATE_IDLE:
        {
            currentIdleDuration_ += delta;
            if (utils::floatGreaterEuqalCompare(currentIdleDuration_, idleDuration_))
            {
                if (changeState(AI_STATE_MOVE))
                {
                    switchDirection(direction_ == LEFT ? RIGHT : LEFT);
                    currentTargetPosition_ = currentTargetPosition_ == initialPosition_ ? autoMoveEndPosition_ : initialPosition_;
                    pAIStateMove_->enter();
                }
            }
        }
            break;
        case AI_STATE_MOVE:
        {
            float currentX = pAISprite->getPositionX();
            float addDistance = delta * speedMove_;
            currentMoveDistance_ += addDistance;
            if (utils::floatGreaterEuqalCompare(currentMoveDistance_, autoMoveDistance_))
            {
                pAISprite->setPositionX(currentTargetPosition_.x);
                stop();
            }
            else
            {
                float nextX = currentX + addDistance * (direction_ == LEFT ? -1 : 1);
                pAISprite->setPositionX(nextX);
            }
        }
            break;
        case AI_STATE_DEAD:
        {
            if (!pAISprite->getActionByTag(AI_ACTION_DEAD_TAG))
            {
                waitForRevival();
            }
        }
            break;
        case AI_STATE_REVIVAL:
        {
            if (!utils::floatEuqalCompare(totalRevivalDuration_, -1))
            {
                currentRevivalDuration_ += delta;
                if (utils::floatGreaterEuqalCompare(currentRevivalDuration_, totalRevivalDuration_))
                {
                    stop();
                }
            }
        }
        default:
            break;
    }
}

void AI::setPosition(const cocos2d::Point &pos)
{
    Point position = Point(pos.x - property_->bodyRect.origin.x, pos.y - property_->bodyRect.origin.y);
    getActorSprite()->setPosition(position);
}

void AI::addAIToLayer(cocos2d::Layer *layer)
{
    layer->addChild(getActorSprite(), ROLE_Z_ORDER - 1);
}

bool AI::changeState(AI_STATE state)
{
    if (mState_ == AI_STATE_DEAD && state != AI_STATE_REVIVAL)
    {
        return  false;
    }
    getActorSprite()->stopAllActions();
    mPrevState_ = mState_;
    mState_ = state;
    return true;
}

void AI::stop()
{
    if (changeState(AI_STATE_IDLE))
    {
        pAIStateIdle_->enter();
    }
}

void AI::attack()
{
    if (changeState(AI_STATE_ATTACK))
    {
        pAIStateAttack_->enter();
    }
}

void AI::dead()
{
    if (changeState(AI_STATE_DEAD))
    {
        pAIStateDead_->enter();
    }
    GameContext::getInstance().cleanAICanAttack(this);
    if (guard_)
    {
        GameContext::getInstance().killBossGuard(1);
    }
    if (bossMove_)
    {
        GameContext::getInstance().subBossBeforeMoveCount(1);
    }
}

void AI::switchDirection(Actor::Direction direction)
{
	Sprite* pAISprite = getActorSprite();
    if (direction_ != direction)
    {
        direction_ = direction;
        pAISprite->setFlippedX(!pAISprite->isFlippedX());
    }
}

Rect AI::getAttackRect()
{
	Sprite* pAISprite = getActorSprite();
    Rect rect = direction_ == RIGHT ? property_->rightAttackRect : property_->leftAttackRect;
    return Rect(pAISprite->getPositionX() + rect.origin.x, pAISprite->getPositionY() + rect.origin.y, rect.size.width, rect.size.height);
}

Rect AI::getCollisionBodyRect()
{
	Sprite* pAISprite = getActorSprite();
    return cocos2d::Rect(pAISprite->getPositionX() + property_->bodyRect.origin.x, pAISprite->getPositionY() + property_->bodyRect.origin.y, property_->bodyRect.size.width, property_->bodyRect.size.height);
}

void AI::waitForRevival()
{
    if (changeState(AI_STATE_REVIVAL))
    {
        pAIStateRevival_->enter();
    }
}

void AI::reset()
{
	Sprite* pAISprite = getActorSprite();
    direction_ = initialDirection_;
    currentTargetPosition_ = initialPosition_;
    
    if (0 == std::strcmp("left", property_->direction.c_str()))
    {
        pAISprite->setFlippedX(initialDirection_ == RIGHT);
    }
    else
    {
        pAISprite->setFlippedX(initialDirection_ == LEFT);
    }

    currentTargetPosition_ = initialPosition_;
    pAISprite->setPosition(initialPosition_);
}

void AI::deadByBomb()
{
    
}

void AI::move()
{
    pAIStateMove_->enter();
}

bool AI::isAttacked(const Rect& attackRect)
{
	if (mState_ == AI_STATE_DEAD || mState_ == AI_STATE_ATTACK || mState_ == AI_STATE_REVIVAL)
	{
		return false;
	}
	else
	{
		return attackRect.intersectsRect(getBodyRect());
	}
}

bool AI::canBeAttack()
{
	return canBeAttack_;
}

bool AI::readyToAttack(const Rect& targetRect)
{
	if (mState_ != AI_STATE_ATTACK  && mState_ != AI_STATE_DEAD && mState_ != AI_STATE_REVIVAL
		&& getAttackRect().intersectsRect(targetRect))
	{
		return true;
	}
	else
	{
		return false;
	}
}

