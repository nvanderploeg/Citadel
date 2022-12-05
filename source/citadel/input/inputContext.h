//
//  inputContext.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-11-09.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//

#ifndef __INPUT_CONTEXT_H__
#define __INPUT_CONTEXT_H__

#include <filesystem>
#include <unordered_map>
#include <list>

#include "JSONSerializable.h"

#include "input.h"

namespace citadel
{
    class InputContext : public IJSONSerializable
    {
    public:
        std::unordered_map<KeyEvent, std::list<std::string>, KeyEventHasher> keyEventMap;
        std::unordered_map<MouseButtonEvent, std::list<std::string>, MouseButtonEventHasher> mouseButtonEventMap;
        std::filesystem::path filepath;

    public:
        InputContext() = default;
        InputContext(const Json::Value& jValue);
        InputContext(const std::filesystem::path& path);

        void AddKeyBind(const KeyEvent& keyEvent, const std::string& label);
        void AddMouseButtonBind(const MouseButtonEvent& mouseButtonEvent, const std::string& label);

        bool Save();

        virtual void serialize(Json::Value& jValue);
        virtual void deserialize(const Json::Value& jValue);
    };
}

#endif // __INPUT_CONTEXT_H__
