//
//  SceneController.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-21.
//
//

#ifndef __mygame__SceneController__
#define __mygame__SceneController__

#include <string>
#include "cocos2d.h"

class SceneController
: public cocos2d::CCObject
{
public:
	static SceneController* s_pCurrentController_;
	static SceneController* getCurrentController()
	{
		return s_pCurrentController_;
	}
public:
	explicit SceneController(const char* fileName);
	virtual ~SceneController();
    
	void run();
    
private:
	std::string fileName_;
};

#endif /* defined(__mygame__SceneController__) */
