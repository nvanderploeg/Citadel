//
//  input.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-11-09.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//

#ifndef __INPUT_H__
#define __INPUT_H__

#include <variant>
#include <functional>

namespace citadel
{
    struct KeyEvent
    {
    public:
        int keycode;
        int action;
        int modifiers;

        bool operator==(const KeyEvent& other) const
        {
            return (keycode == other.keycode && action == other.action && modifiers == other.modifiers);
        }
    };

    struct KeyEventHasher
    {
        std::size_t operator()(const KeyEvent& k) const
        {
            using std::hash;

            return ((hash<int>()(k.keycode)
                ^ (hash<int>()(k.action) << 1)) >> 1)
                ^ (hash<int>()(k.modifiers) << 1);
        }
    };

    struct KeyEventData
    {
        int code;
        int action;
        bool alt;
        bool control;
        bool shift;
        bool system;
    };

    struct MouseButtonEvent
    {
    public:
        int button;
        int action;
        int modifiers;

        bool operator==(const MouseButtonEvent& other) const
        {
            return (button == other.button && action == other.action && modifiers == other.modifiers);
        }
    };

    struct MouseButtonEventHasher
    {
        std::size_t operator()(const MouseButtonEvent& m) const
        {
            using std::hash;

            return ((hash<int>()(m.button)
                ^ (hash<int>()(m.action) << 1)) >> 1)
                ^ (hash<int>()(m.modifiers) << 1);
        }
    };

    struct MouseButtonEventData
    {
        int code;
        bool alt;
        bool control;
        bool shift;
        bool system;
    };

    struct MouseMoveEventData
    {
        int xPosition;
        int yPosition;
    };

    struct MouseScrollEventData
    {
        double xOffset;
        double yOffset;
    };

    typedef std::variant<KeyEventData, MouseButtonEventData, MouseMoveEventData, MouseScrollEventData> InputEventData;
    typedef std::function<bool(InputEventData&)> InputEventCallback;
}

#endif // __INPUT_H__
