#include <iostream>

#include <GLFW/glfw3.h>

#include "serializer.h"

#include "inputRouter.h"
#include "inputContext.h"

namespace citadel
{
    InputRouter::InputRouter()
    {

    }

    void InputRouter::BindToGLFW(GLFWwindow* window)
    {
        inputContext = std::make_shared<InputContext>();

        // NOTE: Binding the inputRouter to the window.
        // This must not be overwritten by anyone else or these callbacks won't work.
        glfwSetWindowUserPointer(window, this);

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            // Grab a reference to ourselves from the window; set previously, above.
            InputRouter * router = static_cast<InputRouter*>(glfwGetWindowUserPointer(window));
            KeyEvent keyEvent = { key, action, mods };
            // get a list of all labels bound to this key event
            auto labelListItr = router->inputContext->keyEventMap.find(keyEvent);
            if (labelListItr != router->inputContext->keyEventMap.end())
            {
                KeyEventData keyData = {key, static_cast<bool>(mods | GLFW_MOD_ALT),
                                            static_cast<bool>(mods | GLFW_MOD_CONTROL),
                                            static_cast<bool>(mods | GLFW_MOD_SHIFT),
                                            static_cast<bool>(mods | GLFW_MOD_SUPER)};
                InputEventData eventData = keyData;
                // go through each label
                for (auto labelItr = labelListItr->second.begin(); labelItr != labelListItr->second.end(); ++labelItr)
                {
                    // get a list of callbacks bound to this label
                    auto callbackListItr = router->callbackMap.find(*labelItr);
                    if (callbackListItr != router->callbackMap.end())
                    {
                        // call each callback, passing back the key event data
                        for (auto callbackItr = callbackListItr->second.begin(); callbackItr != callbackListItr->second.end(); ++callbackItr)
                        {
                            InputEventCallback keyCallback = *callbackItr;
                            keyCallback(eventData);
                        }
                    }
                }
            }
            //std::cout << "Key Callback" << std::endl << key << "," << scancode << "," << action << "," << mods << std::endl;
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
            InputRouter * router = static_cast<InputRouter*>(glfwGetWindowUserPointer(window));
            // std::cout << "MousePos Callback" << std::endl << "(" << x << ", " << y << ")" << std::endl;
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            // Grab a reference to ourselves from the window; set previously, above.
            InputRouter* router = static_cast<InputRouter*>(glfwGetWindowUserPointer(window));
            MouseButtonEvent buttonEvent = { button, action, mods };
            // get a list of all labels bound to this key event
            auto labelListItr = router->inputContext->mouseButtonEventMap.find(buttonEvent);
            if (labelListItr != router->inputContext->mouseButtonEventMap.end())
            {
                MouseButtonEventData buttonData = { button, static_cast<bool>(mods | GLFW_MOD_ALT),
                                            static_cast<bool>(mods | GLFW_MOD_CONTROL),
                                            static_cast<bool>(mods | GLFW_MOD_SHIFT),
                                            static_cast<bool>(mods | GLFW_MOD_SUPER) };
                InputEventData eventData = buttonData;
                // go through each label
                for (auto labelItr = labelListItr->second.begin(); labelItr != labelListItr->second.end(); ++labelItr)
                {
                    // get a list of callbacks bound to this label
                    auto callbackListItr = router->callbackMap.find(*labelItr);
                    if (callbackListItr != router->callbackMap.end())
                    {
                        // call each callback, passing back the key event data
                        for (auto callbackItr = callbackListItr->second.begin(); callbackItr != callbackListItr->second.end(); ++callbackItr)
                        {
                            InputEventCallback buttonCallback = *callbackItr;
                            buttonCallback(eventData);
                        }
                    }
                }
            }
            //std::cout << "Click Callback" << std::endl << button << "," << action << "," << mods << std::endl;
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
            InputRouter * router = static_cast<InputRouter*>(glfwGetWindowUserPointer(window));
            std::cout << "MouseScroll Callback" << std::endl << "(" << xoffset << ", " << yoffset << ")" << std::endl;
            for (auto& callback : router->callbackMap["mouseScroll"]) {
                InputEventData data(MouseScrollEventData({xoffset,yoffset}));
                if(callback(data)) {
                    break;
                }
            }
        });
    }

    void InputRouter::AddEventWithCallback(const std::string& label, const KeyEvent& keyEvent, InputEventCallback callback)
    {
        BindCallbackToLabel(label, callback);
        inputContext->AddKeyBind(keyEvent, label);
    }

    void InputRouter::BindCallbackToLabel(const std::string & label, InputEventCallback callback)
    {
        callbackMap[label].push_back(callback);
    }
    
    void InputRouter::SetInputContext(const Json::Value& jValue)
    {
        if (inputContext == nullptr)
            inputContext = std::make_shared<InputContext>(jValue);
        else
            inputContext->deserialize(jValue);
    }
    bool InputRouter::Save()
    {
        return inputContext->Save();
    }
}
