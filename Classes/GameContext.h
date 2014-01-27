//
//  GameContext.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-22.
//
//

#ifndef __mygame__GameContext__
#define __mygame__GameContext__

#include "cocos2d.h"
#include "Role.h"
#include "Ladder.h"
#include "AI.h"
#include "Wall.h"
#include "Boss.h"

class Box;
class GameLogic;

class GameContext
{
public:
    typedef std::vector<SceneObject*> SceneObjectArray;
    typedef std::vector<AI*> AIArray;
    typedef std::vector<Wall*> WallArray;
    typedef std::vector<Box*> BoxArray;
    typedef std::list<std::string> MapList;
    typedef std::vector<Boss*> BossArray;
    
public:
    bool initTiledMap(const char* tmxFile);
    void initMapObjects(cocos2d::TMXTiledMap* map);
    void updateGameContext(float delta);
    void addSceneObjectsToLayer(cocos2d::Layer* layer);
    void addAIsToLayer(cocos2d::Layer* layer);
    void addBossToLayer(cocos2d::Layer* layer);
    void cleanAICanAttack(AI* ai);
    void cleanBossCanAttack(Boss* boss);
    void goToNextMap();
    void initNextTiledMap();
    void gameVictory();
    void gameOver();
    void clear();
    void addKillCount(unsigned int add);
    bool hasBomb();
    void bombExplode();
    void killBossGuard(unsigned int count);
    bool allMapFinished();
    void resetMapInfo();
    void addBomb(unsigned int count);
    void subBossBeforeMoveCount(unsigned int count);
    void showBossItem();
    void pickUpBossItem();
    const char* getCurrentMapName();
    void initData();
    
public:
    static GameContext& getInstance()
    {
        static GameContext context;
        return context;
    }
    
private:
    GameContext();
    GameContext(const GameContext&);
    GameContext& operator =(const GameContext&);
    
public:
    ~GameContext();
    
    cocos2d::TMXTiledMap* getMap() const
    {
        return pTiledMap_;
    }
    
    Role* getRole()
    {
        return pRole_;
    }
    
    SceneObjectArray& getLadderArray()
    {
        return ladderArray_;
    }
    
    AIArray& getAIArray()
    {
        return aiArray_;
    }
    
    WallArray& getWallArray()
    {
        return wallArray_;
    }
    
    BoxArray& getBoxArray()
    {
        return boxArray_;
    }
    
    BossArray& getBossArray()
    {
        return bossArray_;
    }
    
    const std::string& getMapName()
    {
        return mapList.front();
    }
    
private:
    MapList mapList;
    cocos2d::TMXTiledMap* pTiledMap_;
    cocos2d::TMXTiledMap* pTiledMap2_;
    Role* pRole_;
    SceneObjectArray ladderArray_;
    AIArray aiArray_;
    WallArray wallArray_;
    BoxArray boxArray_;
    BossArray bossArray_;
    
    CC_SYNTHESIZE(AI*, aiCanAttack_, AICanAttack);
    CC_SYNTHESIZE(Boss*, bossCanAttack_, BossCanAttack);
    CC_SYNTHESIZE(GameLogic*, gameLogic_, GameLogic);
    CC_SYNTHESIZE(unsigned int, lightCount, LightCount);
    CC_SYNTHESIZE(cocos2d::Rect, bombInitialRect, BombInitialRect);
    CC_SYNTHESIZE(cocos2d::Rect, bombMovedRect, BombMovedRect);
    CC_SYNTHESIZE(float, currentOffsetY, CurrentOffsetY);
    CC_SYNTHESIZE(float, offsetYChangeOnce, OffsetYChangeOnce);
    CC_SYNTHESIZE(float, upEdgeForChangeOffsetY, UpEdgeForChangeOffsetY);
    CC_SYNTHESIZE(float, downEdgeForChangeOffsetY, DownEdgeForChangeOffsetY);
    CC_SYNTHESIZE(bool, bossItem_, BossItem);
};

#endif /* defined(__mygame__GameContext__) */
