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
class Box;
class Boss;

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
        GAME_STATUS_VICTORY,
        GAME_STATUS_SWITCH_MAP,
        GAME_STATUS_LOAD_NEXT_MAP,
    };
    
public:
    class IObserver
    {
    public:
        virtual ~IObserver(){};
        virtual void onStatusChanged(GameStatus prevStatus, GameStatus status) = 0;
        virtual void onLadderCanClimb(Ladder* ladder, bool isCanUp) = 0;
        virtual void onLadderCanNotClimb(Ladder* ladder) = 0;
        virtual void onBoxCanOpen(Box* box) = 0;
        virtual void onBoxCanPickUp(Box* box) = 0;
        virtual void onSwitchMap(cocos2d::TMXTiledMap* map) = 0;
        virtual void onSwitchMapProgressUpdate(float offset) = 0;
        virtual void updateLightAndBomb(unsigned int count) = 0;
        virtual void onBombMoved(const cocos2d::Point& add) = 0;
        virtual void onBombExplode() = 0;
        virtual void moveLayerUp() = 0;
        virtual void moveLayerDown() = 0;
        virtual void onBossItemShowed(Boss* boss) = 0;
        virtual void onBossItemPickUped() = 0;
        virtual void showVictoryAnimation(cocos2d::Sprite* sprite) = 0;
    };
    
public:
    explicit GameLogic(IObserver& observer);
    virtual ~GameLogic();
    
public:
    void update(float delta);
    void addMapToLayer(cocos2d::Layer* layer);
//    void climbLadder(Ladder* ladder);
    void switchToNextMap(float switchDistance, cocos2d::TMXTiledMap* map);
    void showSwitchAnimation();
    void updateLightAndBomb(unsigned int count);
    void addBossItem(Boss* boss);
    void showShuraEye();
    
public:
    bool onTouchBegan(cocos2d::Layer* layer, cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchMoved(cocos2d::Layer* layer, cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchEnded(cocos2d::Layer* layer, cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchCancelled(cocos2d::Layer* layer, cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
private:
    bool checkCollision(const cocos2d::Rect& rect1, const cocos2d::Rect& rect2);
    bool checkBombMove(const cocos2d::Point& pos);
    void dealCollisionRoleAndBoss();
    void dealCollsionRoleAndAI();
    void dealCollisionRoleAndLadder();
    void dealCollisionRoleAndBox();
    void dealCollisionRoleAndWall();
    void dealCollisionBombAndAI();
    void dealChangeMapOffsetY();
    void checkMapPass();
    
private:
    IObserver& observer_;
    GameStatus status_;
    
    bool touch_;
    bool move_;
    bool bombMove_;
    CC_SYNTHESIZE(bool, changeY_, ChangeY);
    cocos2d::Point bombMovePosition_;
    float switchMapProgress_;
    float switchMapSpeed_;
    float switchDistance_;
    cocos2d::Repeat* repeat_;
    cocos2d::Sprite* sprite_;
};

#endif /* defined(__mygame__GameLogic__) */
