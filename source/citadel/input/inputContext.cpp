//
//  inputContext.cpp
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-11-09.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//

#include <iostream>

#include "serializer.h"

#include "inputContext.h"

namespace citadel
{
    InputContext::InputContext(const Json::Value& jValue)
    {
        deserialize(jValue);
    }

    InputContext::InputContext(const std::filesystem::path& path)
    {
        filepath = path;
        Json::Value jContext = Serializer::loadFile(filepath);
        if (jContext == Json::nullValue)
        {
            std::cout << "WARNING: InputContext file not found; using default values." << std::endl;
            Serializer::serialize(this, filepath);
            std::cout << "INFO: Generated default input configuration at: " << filepath << std::endl;
        }
        else
        {
            deserialize(jContext);
        }
    }

    void InputContext::AddKeyBind(const KeyEvent& keyEvent, const std::string& label)
    {
        keyEventMap[keyEvent].push_back(label);
    }

    bool InputContext::Save()
    {
        return false;
        // TODO: enable this line once serialize() is implemented;
        return Serializer::serialize(this, filepath);
    }

    void InputContext::serialize(Json::Value& jValue)
    {
        // TODO:
    }

    void InputContext::deserialize(const Json::Value& jValue)
    {
        // loop through each member in the json object
        for (Json::Value::const_iterator labelListItr = jValue.begin(); labelListItr != jValue.end(); ++labelListItr)
        {
            // each member name is our event label; loop through each keyEvent to bind to this label
            std::string label = labelListItr.memberName();
            for (Json::Value::const_iterator keyEventItr = (*labelListItr).begin(); keyEventItr != (*labelListItr).end(); ++keyEventItr)
            {
                Json::Value jBinding = (*keyEventItr);
                KeyEvent keyEvent = {jBinding["key"].asInt(), jBinding["action"].asInt(), jBinding["modifiers"].asInt()};
                AddKeyBind(keyEvent, label);
            }
        }
    }
}
/* NOTE: Below is a sample inputContext.cfg file. The (de)serializers should follow this pattern.
{
    "moveUp" :
    [
        {
            "key" : 87,
            "action": 1,
            "modifiers": 0
        },
        {
            "key" : 265,
            "action": 1,
            "modifiers": 0
        }
    ],
    "moveRight" :
    [
        {
            "key" : 68,
            "action": 1,
            "modifiers": 0
        },
        {
            "key" : 262,
            "action": 1,
            "modifiers": 0
        }
    ]
}
*/
