#pragma once

#include <map>
#include <list>

#include "input.h"

class GLFWwindow;

namespace citadel
{
    class InputContext;

    class InputRouter
    {
    public:
        // a list of callbacks, mapped to an event label
        std::map<std::string, std::list<InputEventCallback> > callbackMap;
        // a pointer to the current context
        std::shared_ptr<InputContext> inputContext;

    public:
        InputRouter();

        void BindToGLFW(GLFWwindow* window);

        void AddEventWithCallback(const std::string& label, const KeyEvent& keyEvent, InputEventCallback callback);
        void BindCallbackToLabel(const std::string& label, InputEventCallback callback);

        void SetInputContext(const Json::Value& jValue);

        bool Save();
    };    
}
