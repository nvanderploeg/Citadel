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
        keyEventMap[keyEvent].insert(label);
    }

    void InputContext::AddMouseButtonBind(const MouseButtonEvent& mouseButtonEvent, const std::string& label)
    {
        mouseButtonEventMap[mouseButtonEvent].insert(label);
    }

    bool InputContext::Save()
    {
        return false;
        // TODO: enable this line once serialize() is implemented;
        //return Serializer::serialize(this, filepath);
    }

    void InputContext::serialize(Json::Value& jValue)
    {
        // TODO:
    }

    void InputContext::deserialize(const Json::Value& jValue)
    {
        // KEYBOARD
        const Json::Value jKeyEvents = jValue["keyEvents"];
        for (Json::Value::const_iterator labelListItr = jKeyEvents.begin(); labelListItr != jKeyEvents.end(); ++labelListItr)
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

        // MOUSE
        const Json::Value jMouseButtonEvents = jValue["mouseButtonEvents"];
        for (Json::Value::const_iterator labelListItr = jMouseButtonEvents.begin(); labelListItr != jMouseButtonEvents.end(); ++labelListItr)
        {
            std::string label = labelListItr.memberName();
            Json::Value jBinding = (*labelListItr);
            MouseButtonEvent buttonEvent = { jBinding["button"].asInt(), jBinding["action"].asInt(), jBinding["modifiers"].asInt() };
            AddMouseButtonBind(buttonEvent, label);
        }
    }
}
/* NOTE: Below is a sample inputContext.cfg file. The (de)serializers should follow this pattern.
{
    "keyEvents":
    {
        "moveRight" :
        [

            {
                "action" : 1,
                "key" : 68,
                "modifiers" : 0
            },

            {
                "action" : 1,
                "key" : 262,
                "modifiers" : 0
            }
        ],
        "moveUp" :
        [

            {
                "action" : 1,
                "key" : 87,
                "modifiers" : 0
            },

            {
                "action" : 1,
                "key" : 265,
                "modifiers" : 0
            }
        ],
        "terminate" :
        [

            {
                "action" : 1,
                "key" : 256,
                "modifiers" : 0
            }
        ]
    },
    "mouseButtonEvents":
    {
        "mouseClick" :
        {
            "button": 0,
            "action": 1,
            "modifiers": 0
        }
    }
}
*/
