#pragma once

#include <variant>
#include <functional>
#include <unordered_map>
#include "GLFW/glfw3.h"

namespace citadel
{
    class KeyEvent
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
            using std::size_t;
            using std::hash;
            using std::string;

            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:

            return ((hash<int>()(k.keycode)
                ^ (hash<int>()(k.action) << 1)) >> 1)
                ^ (hash<int>()(k.modifiers) << 1);
        }
    };

    struct KeyEventData
    {
        int code;
        bool alt;
        bool control;
        bool shift;
        bool system;
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

    class InputRouter
    {
    public:
        std::unordered_map<KeyEvent, InputEventCallback, KeyEventHasher> keyInputMap;

    public:
        InputRouter();

        void BindToGLFW(GLFWwindow* window);

        void MapKey(KeyEvent keyEvent, InputEventCallback callback);


    };    
}
