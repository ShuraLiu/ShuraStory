//
//  Game.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#ifndef __mygame__Game__
#define __mygame__Game__

class GameSceneController;
class LoadingSceneController;
class HomeSceneController;
class GameOverSceneController;

enum SwitchActivityParam{
    LOADING_FINISHED,
    READY_TO_PLAY,
    GAME_OVER,
};

class Game
{
private:
    bool running_;
    GameSceneController* pGameSceneController_;
    LoadingSceneController* pLoadingSceneController_;
    HomeSceneController* pHomeSceneController_;
    GameOverSceneController* pGameOverSceneController_;
    
private:
    Game();
    Game(const Game&);
    Game& operator =(const Game&);
    
public:
    virtual ~Game();
    
    static Game& getInstance()
    {
        static Game instance;
        return instance;
    }
    
public:
    void launch();
    void shutdown();
    
    bool isRunning() const;
    
    void switchActivity(SwitchActivityParam param);
};

#endif /* defined(__mygame__Game__) */
