//
//  ActorFactory.h
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#ifndef __mygame__ActorFactory__
#define __mygame__ActorFactory__

#include "cocos2d.h"
#include "ActorProperty.h"

class ActorFactory
: public cocos2d::SAXDelegator
{
    typedef std::map<std::string, ActorProperty> ActorPropertyArray;
    
    ActorPropertyArray actorPropertyArray_;
    
public:
    void parseFile(const char *fileName);
    ActorProperty* getActorPropertyByName(const char* name);
    
public:
    static ActorFactory& getInstance()
    {
        static ActorFactory factory;
        return factory;
    }
    
public:
    // implement pure virtual methods of CCSAXDelegator
    void startElement(void *ctx, const char *name, const char **attrs);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
    
private:
    ActorFactory(){};
};

#endif /* defined(__mygame__ActorFactory__) */
