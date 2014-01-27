//
//  Role.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#include "Role.h"
#include "RoleStateIdle.h"
#include "RoleStateMove.h"
#include "RoleStatePreClimb.h"
#include "RoleStateClimb.h"
#include "RoleStateAttack.h"
#include "RoleStateDead.h"
#include "RoleStateVictory.h"
#include "config.h"
#include "Ladder.h"
#include "ActorProperty.h"
#include "GameContext.h"

USING_NS_CC;

static const int ATTACK_MENU_TAG = 1;

Role::Role(ActorProperty* property, const cocos2d::Point& initialPosition, const std::string& direction)
: pRoleStateIdle_(new RoleStateIdle(this))
, pRoleStateMove_(new RoleStateMove(this))
, pRoleStatePreClimb_(new RoleStatePreClimb(this))
, pRoleStateClimb_(new RoleStateClimb(this))
, pRoleStateAttack_(new RoleStateAttack(this))
, pRoleStateDead_(new RoleStateDead(this))
, pRoleStateVictory_(new RoleStateVictory(this))
, pCurrentState_(0)
, pRoleSprite_(0)
, speedClimb_(0)
, speedMove_(0)
, mState_(ROLE_STATE_NONE)
, mPrevState_(ROLE_STATE_NONE)
, positionToMove_(Point::ZERO)
, property_(property)
{
    init(initialPosition, direction);
}

Role::~Role()
{
    delete pRoleStateIdle_;
    delete pRoleStateMove_;
    delete pRoleStatePreClimb_;
    delete pRoleStateClimb_;
    delete pRoleStateAttack_;
    delete pRoleStateDead_;
    delete pRoleStateVictory_;
    CC_SAFE_RELEASE_NULL(pRoleSprite_);
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

void Role::init(const cocos2d::Point& initialPosition, const std::string& direction)
{
    pRoleSprite_ = Sprite::create();
    pRoleSprite_->setAnchorPoint(Point::ZERO);
    setPosition(initialPosition);
    CC_SAFE_RETAIN(pRoleSprite_);
    speedMove_ = ROLE_MOVE_SPEED;
    speedClimb_ = ROLE_CLIMB_SPEED;
    
    actions_.resize(ACTION_COUNT, 0);
    RepeatForever* move = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(property_->action_move.c_str())));
    actions_.at(ACTION_MOVE) = move;
    CC_SAFE_RETAIN(move);
    RepeatForever* idle = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(property_->action_idle.c_str())));
    actions_.at(ACTION_IDLE) = idle;
    CC_SAFE_RETAIN(idle);
    Animate* attack = Animate::create(AnimationCache::getInstance()->getAnimation(property_->action_attack.c_str()));
    actions_.at(ACTION_ATTACK) = attack;
    attack->setTag(ROLE_ATTACK_TAG);
    CC_SAFE_RETAIN(attack);
    Animate* dead = Animate::create(AnimationCache::getInstance()->getAnimation(property_->action_dead.c_str()));
    actions_.at(ACTION_DEAD) = dead;
    dead->setTag(ROLE_DEAD_TAG);
    CC_SAFE_RETAIN(dead);
    Animate* victory = Animate::create(AnimationCache::getInstance()->getAnimation(property_->action_victory.c_str()));
    actions_.at(ACTION_VICTORY) = victory;
    victory->setTag(ROLE_VICTORY_TAG);
    CC_SAFE_RETAIN(victory);
    
    if (0 == std::strcmp(direction.c_str(), "left"))
    {
        direction_ = LEFT;
    }
    else
    {
        direction_ = RIGHT;
    }

    if (0 != std::strcmp(direction.c_str(), property_->direction.c_str()))
    {
        pRoleSprite_->setFlippedX(true);
    }
    
    if (changeState(ROLE_STATE_IDLE))
    {
        pRoleStateIdle_->enter();
    }
}

void Role::reset(const cocos2d::Point &initialPosition, const std::string &direction)
{
    setPosition(initialPosition);
    
   switchDirection((0 == std::strcmp(direction.c_str(), "left") ? LEFT : RIGHT));
    
    if (changeState(ROLE_STATE_IDLE))
    {
        pRoleStateIdle_->enter();
    }
}

void Role::update(float delta)
{
    switch (mState_) {
        case ROLE_STATE_MOVE:
        {
            float currentX = pRoleSprite_->getPositionX();
            float nextX = currentX + delta * speedMove_ * (positionToMove_.x > currentX ? 1 : -1);
            if ((currentX - positionToMove_.x) * (nextX - positionToMove_.x) < 0)
            {
                pRoleSprite_->setPositionX(positionToMove_.x);
                stop();
            }
            else
            {
                pRoleSprite_->setPositionX(nextX);
            }
        }
            break;
        case ROLE_STATE_PRE_CLIMB:
        {
            float currentX = pRoleSprite_->getPositionX();
            float nextX = currentX + delta * speedMove_ * (positionBeforeClimb_.x > currentX ? 1 : -1);
            if ((currentX - positionBeforeClimb_.x) * (nextX - positionBeforeClimb_.x) < 0)
            {
                pRoleSprite_->setPositionX(positionBeforeClimb_.x);
                if (changeState(ROLE_STATE_CLIMB))
                {
                    pRoleStateClimb_->enter();
                }
            }
            else
            {
                pRoleSprite_->setPositionX(nextX);
            }
        }
            break;
        case ROLE_STATE_CLIMB:
        {
            float currentY = pRoleSprite_->getPositionY();
            float nextY = currentY + delta * speedClimb_ * (positionAfterClimb_.y > currentY ? 1 : -1);
            if ((currentY - positionAfterClimb_.y) * (nextY - positionAfterClimb_.y) < 0)
            {
                pRoleSprite_->setPositionY(positionAfterClimb_.y);
                stop();
            }
            else
            {
                pRoleSprite_->setPositionY(nextY);
            }
        }
            break;
        case ROLE_STATE_ATTACK:
        {
            if (!pRoleSprite_->getActionByTag(ROLE_ATTACK_TAG))
            {
                stop();
            }
        }
            break;
        case ROLE_STATE_DEAD:
        {
            if (!pRoleSprite_->getActionByTag(ROLE_DEAD_TAG))
            {
                GameContext::getInstance().gameOver();
            }
        }
            break;
        default:
            break;
    }
    if (mState_ == ROLE_STATE_MOVE)
    {
        
    }
    else if (mState_ == ROLE_STATE_PRE_CLIMB)
    {
        
    }
}

void Role::setPosition(const cocos2d::Point &pos)
{
    Point position = Point(pos.x - property_->bodyRect.origin.x, pos.y - property_->bodyRect.origin.y);
    pRoleSprite_->setPosition(position);
}

void Role::addRoleToLayer(cocos2d::Layer *layer)
{
    layer->addChild(pRoleSprite_, ROLE_Z_ORDER);
}

void Role::moveTo(const cocos2d::Point &pos)
{
    if (changeState(ROLE_STATE_MOVE))
    {
        const Rect& bodyRect = getBodyRect();
        if (pos.y >= bodyRect.origin.y && pos.y < bodyRect.origin.y + bodyRect.size.height * 2)
        {
            positionToMove_.x = pos.x - (bodyRect.origin.x + bodyRect.size.width / 2) + pRoleSprite_->getPositionX();
            positionToMove_.y = pRoleSprite_->getPositionY();
            switchDirection(positionToMove_.x < pRoleSprite_->getPositionX() ? LEFT : RIGHT);
            pRoleStateMove_->enter();
        }
    }
}

void Role::climb(Ladder *ladder, bool isClimbUp)
{
    auto pSpriteLadder = ladder->getSpriteLadder();
    Point midDown = Point(pSpriteLadder->getPositionX() + pSpriteLadder->getContentSize().width / 2, pSpriteLadder->getPositionY());
    Point midUp = Point(pSpriteLadder->getPositionX() + pSpriteLadder->getContentSize().width / 2, pSpriteLadder->getPositionY() + pSpriteLadder->getContentSize().height);
    
    Point p1 = Point(midDown.x - property_->bodyRect.origin.x - property_->bodyRect.size.width / 2, midDown.y - property_->bodyRect.origin.y);
    Point p2 = Point(p1.x, midUp.y - property_->bodyRect.origin.y);
    positionBeforeClimb_ = isClimbUp ? p1 : p2;
    positionAfterClimb_ = isClimbUp ? p2 : p1;
    if (changeState(ROLE_STATE_PRE_CLIMB))
    {
        switchDirection(positionBeforeClimb_.x < pRoleSprite_->getPositionX() ? LEFT : RIGHT);
        pRoleStatePreClimb_->enter();
    }
}

bool Role::changeState(ROLE_STATE state)
{
    if (mState_ == ROLE_STATE_DEAD)
    {
        if (state != ROLE_STATE_IDLE)
        {
            return  false;
        }
    }
    if (state == ROLE_STATE_MOVE)
    {
        if (mState_ == ROLE_STATE_PRE_CLIMB || mState_ == ROLE_STATE_CLIMB || mState_ == ROLE_STATE_ATTACK)
        {
            return false;
        }
    }
    pRoleSprite_->stopAllActions();
    mPrevState_ = mState_;
    mState_ = state;
    return true;
}

void Role::stop()
{
    if (changeState(ROLE_STATE_IDLE))
    {
        pRoleStateIdle_->enter();
    }
}

Rect Role::getCollisionBodyRect()
{
    const Rect& bodyRect = property_->bodyRect;
    return cocos2d::Rect(pRoleSprite_->getPositionX() + bodyRect.origin.x, pRoleSprite_->getPositionY() + bodyRect.origin.y, bodyRect.size.width, bodyRect.size.height);
}

void Role::switchDirection(Direction direction)
{
    if (direction_ != direction)
    {
        direction_ = direction;
        pRoleSprite_->setFlippedX(!pRoleSprite_->isFlippedX());
    }
}

Rect Role::getAttackRect()
{
    Rect rect = direction_ == RIGHT ? property_->rightAttackRect : property_->leftAttackRect;
    return Rect(pRoleSprite_->getPositionX() + rect.origin.x, pRoleSprite_->getPositionY() + rect.origin.y, rect.size.width, rect.size.height);
}

void Role::attack()
{
    if (changeState(ROLE_STATE_ATTACK))
    {
        pRoleStateAttack_->enter();
    }
}

void Role::readyToAttack()
{
    if (!pRoleSprite_->getChildByTag(ATTACK_MENU_TAG))
    {
        Sprite* normalSprite = Sprite::createWithSpriteFrameName("button_role_attack.png");
        Sprite* selectedSprite = Sprite::createWithSpriteFrameName("button_role_attack.png");
        MenuItemSprite* item = MenuItemSprite::create(normalSprite, selectedSprite, CC_CALLBACK_1(Role::onMenuAttack, this));
        item->setAnchorPoint(Point(0.5, 0.5));
        item->setPosition(Point::ZERO);
        Menu* menu = Menu::create(item, NULL);
        menu->ignoreAnchorPointForPosition(false);
        menu->setAnchorPoint(Point::ZERO);
        menu->setPosition(Point(pRoleSprite_->getContentSize().width / 2, pRoleSprite_->getContentSize().height * 3 / 2));
        pRoleSprite_->addChild(menu, 1, ATTACK_MENU_TAG);
    }
}

void Role::notReadyToAttack()
{
    if (pRoleSprite_->getChildByTag(ATTACK_MENU_TAG))
    {
        pRoleSprite_->removeChildByTag(ATTACK_MENU_TAG);
    }
}
                                                  
void Role::onMenuAttack(cocos2d::Object *obj)
{
    attack();
    if (GameContext::getInstance().getAICanAttack())
    {
        GameContext::getInstance().getAICanAttack()->dead();
    }
    if (GameContext::getInstance().getBossCanAttack())
    {
        GameContext::getInstance().showBossItem();
        GameContext::getInstance().getBossCanAttack()->dead();
    }
    GameContext::getInstance().addKillCount(1);
}

void Role::runAction(Role::Action action)
{
    pRoleSprite_->runAction(actions_.at(action));
    currentAction_ = action;
}

void Role::dead()
{
    if (changeState(ROLE_STATE_DEAD))
    {
        pRoleStateDead_->enter();
    }
}

void Role::victory()
{
    if (changeState(ROLE_STATE_VICTORY)) {
        pRoleStateVictory_->enter();
    }
}

bool Role::victoryAnimationFinished() const
{
    if (mState_ == ROLE_STATE_VICTORY && !pRoleSprite_->getActionByTag(ROLE_VICTORY_TAG))
    {
        return true;
    }
    return false;
}
