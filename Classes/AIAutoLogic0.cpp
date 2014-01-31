//
//  AIAutoLogic0.cpp
//  ShuraStory
//
//  Created by 刘 潇逸 on 14-1-26.
//
//

#include "AIAutoLogic0.h"
#include "Utils.h"

AIAutoLogic0::AIAutoLogic0(AI* pAI)
: AIAutoLogic(pAI)
{
    
}

AIAutoLogic0::~AIAutoLogic0()
{
    
}

void AIAutoLogic0::doAutoLogic(float delta)
{
    switch (pAI_->getCurrentState())
    {
        case AI_STATE_INITIAL:
        {
            pAI_->setCurrentInitialDuration(pAI_->getCurrentInitialDuration() + delta);
            if (utils::floatGreaterEuqalCompare(pAI_->getCurrentInitialDuration(), pAI_->getInitialDuration()))
            {
                pAI_->stop();
            }
        }
            break;
        case AI_STATE_IDLE:
        {
            pAI_->setCurrentIdleDuration(pAI_->getCurrentIdleDuration() + delta);
            if (utils::floatGreaterEuqalCompare(pAI_->getCurrentIdleDuration(), pAI_->getIdleDuration()))
            {
                if (pAI_->changeState(AI_STATE_MOVE))
                {
                    pAI_->switchDirection(pAI_->getDirection() == AI::LEFT ? AI::RIGHT : AI::LEFT);
                    pAI_->setCurrentTargetPosition((pAI_->getCurrentTargetPosition() == pAI_->getInitialPosition() ? pAI_->getAutoMoveEndPosition() : pAI_->getInitialPosition()));
                    pAI_->move();
                }
            }
        }
            break;
        case AI_STATE_MOVE:
        {
            float currentX = pAI_->getActorSprite()->getPositionX();
            float addDistance = delta * pAI_->getSpeedMove();
            pAI_->setCurrentMoveDistance(pAI_->getCurrentMoveDistance() +addDistance);
            if (utils::floatGreaterEuqalCompare(pAI_->getCurrentMoveDistance(), pAI_->getMoveDistance()))
            {
                pAI_->getActorSprite()->setPositionX(pAI_->getCurrentTargetPosition().x);
                pAI_->stop();
            }
            else
            {
                float nextX = currentX + addDistance * (pAI_->getDirection() == AI::LEFT ? -1 : 1);
                pAI_->getActorSprite()->setPositionX(nextX);
            }
        }
            break;
        case AI_STATE_DEAD:
        {
            if (!pAI_->getActorSprite()->getActionByTag(AI_ACTION_DEAD_TAG))
            {
                pAI_->waitForRevival();
            }
        }
            break;
        case AI_STATE_REVIVAL:
        {
            if (!utils::floatEuqalCompare(pAI_->getTotalRevivalDuration(), -1))
            {
                pAI_->setCurrentRevivalDuration(pAI_->getCurrentRevivalDuration() + delta);
                if (utils::floatGreaterEuqalCompare(pAI_->getCurrentRevivalDuration(), pAI_->getTotalRevivalDuration()))
                {
                    pAI_->stop();
                }
            }
        }
        default:
            break;
    }
}