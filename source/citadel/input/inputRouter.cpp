
#include "inputRouter.h"
#include "serializer.h"
#include <iostream>

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
            // If there is a key mapping for this key, call it's callback.
            auto labelListItr = router->inputContext->keyEventMap.find(keyEvent);
            if (labelListItr != router->inputContext->keyEventMap.end())
            {
                InputEventData eventData = KeyEventData(key, 
                                                    mods | GLFW_MOD_ALT, 
                                                    mods | GLFW_MOD_CONTROL, 
                                                    mods | GLFW_MOD_SHIFT, 
                                                    mods | GLFW_MOD_SUPER);

                for (auto labelItr = labelListItr->second.begin(); labelItr != labelListItr->second.end(); ++labelItr)
                {
                    auto callbackListItr = router->keyInputMap.find(*labelItr);
                    if (callbackListItr != router->keyInputMap.end())
                    {
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
            InputRouter * router = static_cast<InputRouter*>(glfwGetWindowUserPointer(window));
            std::cout << "Click Callback" << std::endl << button << "," << action << "," << mods << std::endl;
        });
        glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
            InputRouter * router = static_cast<InputRouter*>(glfwGetWindowUserPointer(window));
            std::cout << "MouseScroll Callback" << std::endl << "(" << xoffset << ", " << yoffset << ")" << std::endl;
        });
    }

    void InputRouter::AddKeyBind(const std::string& label, const KeyEvent& keyEvent, InputEventCallback callback)
    {
        SetKeyCallback(label, callback);
        inputContext->AddKeyBind(keyEvent, label);
    }

    void InputRouter::SetKeyCallback(const std::string & label, InputEventCallback callback)
    {
        keyInputMap[label].push_back(callback);
    }
    
    void InputRouter::SetInputContext(const Json::Value& jValue)
    {
        if (inputContext == nullptr)
            inputContext = std::make_shared<InputContext>(jValue);
        else
            inputContext->deserialize(jValue);
    }
    
    InputContext::InputContext()
    {
    }

    InputContext::InputContext(const Json::Value& jValue)
    {
        deserialize(jValue);
    }

    InputContext::InputContext(const std::filesystem::path& path)
    {
        Json::Value jContext = Serializer::loadFile(path);
        if (jContext == Json::nullValue)
        {

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

    void InputContext::serialize(Json::Value& jValue)
    {
    }
    
    void InputContext::deserialize(const Json::Value& jValue)
    {
        for (auto itr = jValue.begin(); itr != jValue.end(); ++itr)
        {
            std::cout << itr.index() << ":" << itr.key().asString() << ":" << itr.memberName() << std::endl;
            std::cout << jValue[itr.index()].type() << std::endl;
            Json::Value jObj = jValue[itr.index()];
            auto memberNames = jObj.getMemberNames();
            auto label = memberNames[0];
            for (auto itr2 = jObj[label].begin(); itr2 != jObj[label].end(); ++itr2)
            {
                Json::Value jBinding = jObj[label][itr2.index()];
                KeyEvent keyEvent(jBinding["key"].asInt(), jBinding["action"].asInt(), jBinding["modifiers"].asInt());
                keyEventMap[keyEvent].push_back(label);
            }
        }
    }
}