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

class Game
{
private:
    bool running_;
    GameSceneController* pGameSceneController_;
    
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
};

#endif /* defined(__mygame__Game__) */
