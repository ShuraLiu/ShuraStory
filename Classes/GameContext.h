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

class GameContext
{
public:
    typedef std::vector<SceneObject*> SceneObjectArray;
    typedef std::vector<AI*> AIArray;
public:
    bool initTiledMap(const char* tmxFile);
    void updateGameContext(float delta);
    void addSceneObjectsToLayer(cocos2d::Layer* layer);
    void addAIsToLayer(cocos2d::Layer* layer);
    void cleanAICanAttack(AI* ai);
    
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
    
private:
    cocos2d::TMXTiledMap* pTiledMap_;
    Role* pRole_;
    SceneObjectArray ladderArray_;
    AIArray aiArray_;
    
    CC_SYNTHESIZE(AI*, aiCanAttack_, AICanAttack);
};

#endif /* defined(__mygame__GameContext__) */
