//
//  ActorFactory.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#include "ActorFactory.h"

USING_NS_CC;

void ActorFactory::startElement(void *ctx, const char *name, const char **attrs)
{
    CC_UNUSED_PARAM(ctx);
    
    if (0 == std::strcmp("Role", name))
    {
        ActorProperty property;
        for(int i = 0; attrs[i]; i += 2)
        {
            const char* key = attrs[i];
            const char* value = attrs[i+1];
            if (0 == std::strcmp("name", key))
            {
                property.name = value;
            }
            if (0 == std::strcmp("action_idle", key))
            {
                property.action_idle = value;
            }
            if (0 == std::strcmp("action_move", key))
            {
                property.action_move = value;
            }
            if (0 == std::strcmp("action_attack", key))
            {
                property.action_attack = value;
            }
            if (0 == std::strcmp("action_attacked", key))
            {
                property.action_attacked = value;
            }
            if (0 == std::strcmp("action_dead", key))
            {
                property.action_dead = value;
            }
            if (0 == std::strcmp("action_victory", key))
            {
                property.action_victory = value;
            }
            if (0 == std::strcmp("action_climb", key))
            {
                property.action_climb = value;
            }
            if (0 == std::strcmp("direction", key))
            {
                property.direction = value;
            }
            if (0 == std::strcmp("body_rect_x", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.bodyRect.origin.x = v;
            }
            if (0 == std::strcmp("body_rect_y", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.bodyRect.origin.y = v;
            }
            if (0 == std::strcmp("body_rect_width", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.bodyRect.size.width = v;
            }
            if (0 == std::strcmp("body_rect_height", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.bodyRect.size.height = v;
            }
            if (0 == std::strcmp("left_attack_rect_x", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.leftAttackRect.origin.x = v;
            }
            if (0 == std::strcmp("left_attack_rect_y", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.leftAttackRect.origin.y = v;
            }
            if (0 == std::strcmp("left_attack_rect_width", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.leftAttackRect.size.width = v;
            }
            if (0 == std::strcmp("left_attack_rect_height", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.leftAttackRect.size.height = v;
            }
            if (0 == std::strcmp("right_attack_rect_x", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.rightAttackRect.origin.x = v;
            }
            if (0 == std::strcmp("right_attack_rect_y", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.rightAttackRect.origin.y = v;
            }
            if (0 == std::strcmp("right_attack_rect_width", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.rightAttackRect.size.width = v;
            }
            if (0 == std::strcmp("right_attack_rect_height", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.rightAttackRect.size.height = v;
            }
            if (0 == std::strcmp("direction", key))
            {
                property.direction = value;
            }
        }
        actorPropertyArray_.insert(ActorPropertyArray::value_type(property.name, property));
    }
    else if (0 == std::strcmp("AI", name))
    {
        ActorProperty property;
        for(int i = 0; attrs[i]; i += 2)
        {
            const char* key = attrs[i];
            const char* value = attrs[i+1];
            if (0 == std::strcmp("name", key))
            {
                property.name = value;
            }
            if (0 == std::strcmp("action_idle", key))
            {
                property.action_idle = value;
            }
            if (0 == std::strcmp("action_move", key))
            {
                property.action_move = value;
            }
            if (0 == std::strcmp("action_attack", key))
            {
                property.action_attack = value;
            }
            if (0 == std::strcmp("action_attacked", key))
            {
                property.action_attacked = value;
            }
            if (0 == std::strcmp("action_dead", key))
            {
                property.action_dead = value;
            }
            if (0 == std::strcmp("direction", key))
            {
                property.direction = value;
            }
            if (0 == std::strcmp("body_rect_x", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.bodyRect.origin.x = v;
            }
            if (0 == std::strcmp("body_rect_y", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.bodyRect.origin.y = v;
            }
            if (0 == std::strcmp("body_rect_width", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.bodyRect.size.width = v;
            }
            if (0 == std::strcmp("body_rect_height", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.bodyRect.size.height = v;
            }
            if (0 == std::strcmp("left_attack_rect_x", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.leftAttackRect.origin.x = v;
            }
            if (0 == std::strcmp("left_attack_rect_y", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.leftAttackRect.origin.y = v;
            }
            if (0 == std::strcmp("left_attack_rect_width", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.leftAttackRect.size.width = v;
            }
            if (0 == std::strcmp("left_attack_rect_height", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.leftAttackRect.size.height = v;
            }
            if (0 == std::strcmp("right_attack_rect_x", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.rightAttackRect.origin.x = v;
            }
            if (0 == std::strcmp("right_attack_rect_y", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.rightAttackRect.origin.y = v;
            }
            if (0 == std::strcmp("right_attack_rect_width", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.rightAttackRect.size.width = v;
            }
            if (0 == std::strcmp("right_attack_rect_height", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.rightAttackRect.size.height = v;
            }
            if (0 == std::strcmp("direction", key))
            {
                property.direction = value;
            }
        }
        actorPropertyArray_.insert(ActorPropertyArray::value_type(property.name, property));
    }
    else if (0 == std::strcmp("Boss", name))
    {
        ActorProperty property;
        for(int i = 0; attrs[i]; i += 2)
        {
            const char* key = attrs[i];
            const char* value = attrs[i+1];
            if (0 == std::strcmp("name", key))
            {
                property.name = value;
            }
            if (0 == std::strcmp("action_idle", key))
            {
                property.action_idle = value;
            }
            if (0 == std::strcmp("action_move", key))
            {
                property.action_move = value;
            }
            if (0 == std::strcmp("action_attack", key))
            {
                property.action_attack = value;
            }
            if (0 == std::strcmp("action_dead", key))
            {
                property.action_dead = value;
            }
            if (0 == std::strcmp("action_notbeat", key))
            {
                property.action_notbeat = value;
            }
            if (0 == std::strcmp("direction", key))
            {
                property.direction = value;
            }
            if (0 == std::strcmp("body_rect_x", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.bodyRect.origin.x = v;
            }
            if (0 == std::strcmp("body_rect_y", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.bodyRect.origin.y = v;
            }
            if (0 == std::strcmp("body_rect_width", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.bodyRect.size.width = v;
            }
            if (0 == std::strcmp("body_rect_height", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.bodyRect.size.height = v;
            }
            if (0 == std::strcmp("left_attack_rect_x", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.leftAttackRect.origin.x = v;
            }
            if (0 == std::strcmp("left_attack_rect_y", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.leftAttackRect.origin.y = v;
            }
            if (0 == std::strcmp("left_attack_rect_width", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.leftAttackRect.size.width = v;
            }
            if (0 == std::strcmp("left_attack_rect_height", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.leftAttackRect.size.height = v;
            }
            if (0 == std::strcmp("right_attack_rect_x", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.rightAttackRect.origin.x = v;
            }
            if (0 == std::strcmp("right_attack_rect_y", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.rightAttackRect.origin.y = v;
            }
            if (0 == std::strcmp("right_attack_rect_width", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.rightAttackRect.size.width = v;
            }
            if (0 == std::strcmp("right_attack_rect_height", key))
            {
                std::stringstream ss;
                float v;
                ss << value;
                ss >> v;
                property.rightAttackRect.size.height = v;
            }
            if (0 == std::strcmp("direction", key))
            {
                property.direction = value;
            }
        }
        actorPropertyArray_.insert(ActorPropertyArray::value_type(property.name, property));
    }
}

void ActorFactory::endElement(void *ctx, const char *name)
{
    
}

void ActorFactory::textHandler(void *ctx, const char *ch, int len)
{
    
}

void ActorFactory::parseFile(const char *fileName)
{
    CCAssert(fileName, "xml file name can not be null");
    SAXParser parser;
    
    if (parser.init("UTF-8"))
    {
        parser.setDelegator(this);
        parser.parse(fileName);
    }
}

ActorProperty* ActorFactory::getActorPropertyByName(const char *name)
{
    ActorPropertyArray::iterator it = actorPropertyArray_.find(std::string(name));
    if (it != actorPropertyArray_.end())
    {
        return &((*it).second);
    }
    return nullptr;
}