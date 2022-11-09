#pragma once

#include <variant>
#include <functional>
#include <map>
#include "GLFW/glfw3.h"

namespace citadel
{
    struct KeyEvent
    {
        int code;
        bool alt;
        bool control;
        bool shift;
        bool system;
    };

    struct MouseButtonEvent
    {
        int code;
        bool alt;
        bool control;
        bool shift;
        bool system;
    };

    struct MouseMoveEvent
    {
        int xPosition;
        int yPosition;
    };

    struct MouseScrollEvent
    {
        double xOffset;
        double yOffset;
    };

    typedef std::variant<KeyEvent, MouseButtonEvent, MouseMoveEvent, MouseScrollEvent> InputEventData;
    typedef std::function<bool(InputEventData&)> InputEventCallback;

    class InputRouter
    {
    public:
        std::map<int, InputEventCallback> keyInputMap;

    public:
        InputRouter();

        void BindToGLFW(GLFWwindow* window);

        void MapKey(int key, InputEventCallback callback);


    };    
}
