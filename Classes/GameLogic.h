//
//  GameLogic.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#ifndef __mygame__GameLogic__
#define __mygame__GameLogic__

#include "cocos2d.h"

class GameScene;
class Ladder;

class GameLogic
{
public:
    enum GameStatus
    {
        GAME_STATUS_NONE = 0,
        GAME_STATUS_INIT,
        GAME_STATUS_PLAYING,
        GAME_STATUS_PAUSE,
        GAME_STATUS_END,
    };
    
public:
    class IObserver
    {
    public:
        virtual ~IObserver(){};
        virtual void onStatusChanged(GameStatus prevStatus, GameStatus status) = 0;
        virtual void onLadderCanClimb(Ladder* ladder, bool isCanUp) = 0;
        virtual void onLadderCanNotClimb(Ladder* ladder) = 0;
        virtual void onAICanAttack() = 0;
    };
    
public:
    explicit GameLogic(IObserver& observer);
    virtual ~GameLogic();
    
public:
    void update(float delta);
    void addMapToLayer(cocos2d::Layer* layer);
    void climbLadder(Ladder* ladder);
    
public:
    bool onTouchBegan(cocos2d::Layer* layer, cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchMoved(cocos2d::Layer* layer, cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchEnded(cocos2d::Layer* layer, cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchCancelled(cocos2d::Layer* layer, cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
private:
    bool checkCollision(const cocos2d::Rect& rect1, const cocos2d::Rect& rect2);
    void dealCollsionRoleAndAI();
    void dealCollisionRoleAndLadder();
    
private:
    IObserver& observer_;
    GameStatus status_;
    
    bool touch_;
};

#endif /* defined(__mygame__GameLogic__) */
