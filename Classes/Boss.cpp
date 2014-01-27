//
//  Boss.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-25.
//
//

#include "Boss.h"
#include "config.h"
#include "BossStateIdle.h"
#include "BossStateMove.h"
#include "BossStateAttack.h"
#include "BossStateDead.h"
#include "BossStateUnbeatable.h"
#include "BossStateRevival.h"
#include "Utils.h"
#include "ActorProperty.h"
#include "GameContext.h"
#include "BossStateNotMove.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

const static int BOSS_ACTION_DEAD_TAG = 201;

Boss::Boss(ActorProperty* property, const cocos2d::Point& initialPosition, const std::string& direction, float speed, float idleDuration, float moveDistance, float unbeatCount, float revivalDuration, unsigned int beforeMoveCount)
: pBossStateIdle_(new BossStateIdle(this))
, pBossStateMove_(new BossStateMove(this))
, pBossStateAttack_(new BossStateAttack(this))
, pBossStateDead_(new BossStateDead(this))
//, pBossStateUnbeatable_(new BossStateUnbeatable(this))
, pBossStateRevival_(new BossStateRevival(this))
, pBossStateNotMove_(new BossStateNotMove(this))
, pBossStateCurrent_(0)
, pBossSprite_(0)
, speedMove_(speed)
, idleDuration_(idleDuration)
, autoMoveDistance_(moveDistance)
, unbeatCount_(unbeatCount)
, mState_(BOSS_STATE_NONE)
, mPrevState_(BOSS_STATE_NONE)
, autoLogic_(true)
, currentIdleDuration_(0)
, currentMoveDistance_(0)
, currentInitialDuration_(0)
, currentRevivalDuration_(0)
, totalRevivalDuration_(revivalDuration)
, beforeMoveCount_(beforeMoveCount)
, property_(property)
{
    init(initialPosition, direction);
}

Boss::~Boss()
{
    delete pBossStateIdle_;
    delete pBossStateMove_;
    delete pBossStateAttack_;
    delete pBossStateDead_;
    delete pBossStateRevival_;
    delete pBossStateNotMove_;
    
    CC_SAFE_RELEASE_NULL(pBossSprite_);
    CC_SAFE_RELEASE_NULL(pMenuItem_);

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

void Boss::init(const cocos2d::Point& initialPosition, const std::string& direction)
{
    pBossSprite_ = Sprite::create();
    pBossSprite_->setAnchorPoint(Point::ZERO);
    setPosition(initialPosition);
    CC_SAFE_RETAIN(pBossSprite_);
    
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
    dead->setTag(BOSS_ACTION_DEAD_TAG);
    CC_SAFE_RETAIN(dead);
    
    RepeatForever* notbeat = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(property_->action_notbeat.c_str())));
    actions_.at(ACTION_NOT_BEAT) = notbeat;
    CC_SAFE_RETAIN(notbeat);
    
    initMenu();
    
    if (0 == std::strcmp(direction.c_str(), "left"))
    {
        direction_ = LEFT;
    }
    else
    {
        direction_ = RIGHT;
    }
    initialDirection_ = direction_;
    
    initialPosition_ = pBossSprite_->getPosition();
    float x = (direction_ == LEFT) ? (initialPosition_.x + autoMoveDistance_) : (initialPosition_.x - autoMoveDistance_);
    float y = initialPosition_.y;
    autoMoveEndPosition_ = Point(x, y);
    currentTargetPosition_ = initialPosition_;
    
    if (0 != std::strcmp(direction.c_str(), property_->direction.c_str()))
    {
        pBossSprite_->setFlippedX(true);
    }
    
    if (beforeMoveCount_ > 0)
    {
        if (changeState(BOSS_STATE_NOT_MOVE))
        {
            pBossStateNotMove_->enter();
        }
    }
    else
    {
        if (changeState(BOSS_STATE_IDLE))
        {
            pBossStateIdle_->enter();
        }
    }
}

void Boss::update(float delta)
{
    doAutoLogic(delta);
}

void Boss::doAutoLogic(float delta)
{
    switch (mState_) {
//        case BOSS_STATE_INITIAL:
//        {
//            currentInitialDuration_ += delta;
//            if (utils::floatGreaterEuqalCompare(currentInitialDuration_, initialDuration_))
//            {
//                stop();
//            }
//        }
//            break;
        case BOSS_STATE_IDLE:
        {
            currentIdleDuration_ += delta;
            if (utils::floatGreaterEuqalCompare(currentIdleDuration_, idleDuration_))
            {
                if (changeState(BOSS_STATE_MOVE))
                {
                    switchDirection(direction_ == LEFT ? RIGHT : LEFT);
                    currentTargetPosition_ = currentTargetPosition_ == initialPosition_ ? autoMoveEndPosition_ : initialPosition_;
                    pBossStateMove_->enter();
                }
            }
        }
            break;
        case BOSS_STATE_MOVE:
        {
            float currentX = pBossSprite_->getPositionX();
            float addDistance = delta * speedMove_;
            currentMoveDistance_ += addDistance;
            if (utils::floatGreaterEuqalCompare(currentMoveDistance_, autoMoveDistance_))
            {
                pBossSprite_->setPositionX(currentTargetPosition_.x);
                stop();
            }
            else
            {
                float nextX = currentX + addDistance * (direction_ == LEFT ? -1 : 1);
                pBossSprite_->setPositionX(nextX);
            }
        }
            break;
        case BOSS_STATE_DEAD:
        {
            if (!pBossSprite_->getActionByTag(BOSS_ACTION_DEAD_TAG))
            {
                waitForRevival();
            }
        }
            break;
        case BOSS_STATE_REVIVAL:
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

void Boss::setPosition(const cocos2d::Point &pos)
{
    Point position = Point(pos.x - property_->bodyRect.origin.x, pos.y - property_->bodyRect.origin.y);
    pBossSprite_->setPosition(position);
}

void Boss::addBossToLayer(cocos2d::Layer *layer)
{
    layer->addChild(pBossSprite_, ROLE_Z_ORDER - 1);
}

bool Boss::changeState(BOSS_STATE state)
{
    if (state == BOSS_STATE_DEAD && unbeatCount_ > 0)
    {
        return false;
    }
    if (mState_ == BOSS_STATE_DEAD && state != BOSS_STATE_REVIVAL)
    {
        return  false;
    }
    pBossSprite_->stopAllActions();
    mPrevState_ = mState_;
    mState_ = state;
    return true;
}

void Boss::stop()
{
    if (changeState(BOSS_STATE_IDLE))
    {
        pBossStateIdle_->enter();
    }
}

void Boss::attack()
{
    if (changeState(BOSS_STATE_ATTACK))
    {
        pBossStateAttack_->enter();
    }
}

void Boss::dead()
{
    if (changeState(BOSS_STATE_DEAD))
    {
        pBossStateDead_->enter();
    }
    GameContext::getInstance().cleanBossCanAttack(this);
}

void Boss::switchDirection(Actor::Direction direction)
{
    if (direction_ != direction)
    {
        direction_ = direction;
        pBossSprite_->setFlippedX(!pBossSprite_->isFlippedX());
    }
}

Rect Boss::getAttackRect()
{
    Rect rect = direction_ == RIGHT ? property_->rightAttackRect : property_->leftAttackRect;
    return Rect(pBossSprite_->getPositionX() + rect.origin.x, pBossSprite_->getPositionY() + rect.origin.y, rect.size.width, rect.size.height);
}

Rect Boss::getCollisionBodyRect()
{
    return cocos2d::Rect(pBossSprite_->getPositionX() + property_->bodyRect.origin.x, pBossSprite_->getPositionY() + property_->bodyRect.origin.y, property_->bodyRect.size.width, property_->bodyRect.size.height);
}

void Boss::waitForRevival()
{
    if (changeState(BOSS_STATE_REVIVAL))
    {
        pBossStateRevival_->enter();
    }
}

void Boss::reset()
{
    direction_ = initialDirection_;
    currentTargetPosition_ = initialPosition_;
    
    if (0 == std::strcmp("left", property_->direction.c_str()))
    {
        pBossSprite_->setFlippedX(initialDirection_ == RIGHT);
    }
    else
    {
        pBossSprite_->setFlippedX(initialDirection_ == LEFT);
    }
    
    currentTargetPosition_ = initialPosition_;
    pBossSprite_->setPosition(initialPosition_);
}

void Boss::deadByBomb()
{
    
}

void Boss::subShield(unsigned int count)
{
    unbeatCount_ -= count;
}

void Boss::subBeforeMove(unsigned int count)
{
    beforeMoveCount_ -= count;
    if (beforeMoveCount_ <= 0)
    {
//        if (changeState(BOSS_STATE_MOVE))
//        {
//            switchDirection(direction_ == LEFT ? RIGHT : LEFT);
//            currentTargetPosition_ = currentTargetPosition_ == initialPosition_ ? autoMoveEndPosition_ : initialPosition_;
//            pBossStateMove_->enter();
//        }
        stop();
    }
}

void Boss::initMenu()
{
    MenuItemSprite* itemPass = 0;
    
    Sprite* normalSprite = Sprite::createWithSpriteFrameName("button_shura_eye_pickup.png");
    Sprite* selectedSprite = Sprite::createWithSpriteFrameName("button_shura_eye_pickup.png");
    itemPass = MenuItemSprite::create(normalSprite, selectedSprite, CC_CALLBACK_1(Boss::onMenuPass, this));
    itemPass->setAnchorPoint(Point::ZERO);
    itemPass->setPosition(Point::ZERO);

    pMenuItem_ = Menu::create(itemPass, NULL);

    Sprite* temp = Sprite::createWithSpriteFrameName("button_shura_eye_pickup.png");
    pMenuItem_->setContentSize(Size(temp->getContentSize().width, temp->getContentSize().height));
    pMenuItem_->ignoreAnchorPointForPosition(false);
    pMenuItem_->setAnchorPoint(Point(0.5, 0));
//    pMenuItem_->setPosition(Point(pBossSprite_->getPositionX() + pBossSprite_->getContentSize().width / 2, pBossSprite_->getPositionY() + pBossSprite_->getContentSize().height));
    CC_SAFE_RETAIN(pMenuItem_);
}

void Boss::onMenuPass(Object* obj)
{
    SimpleAudioEngine::getInstance()->playEffect("effect_pickup.mp3");
    GameContext::getInstance().pickUpBossItem();
    pMenuItem_->removeFromParent();
}
