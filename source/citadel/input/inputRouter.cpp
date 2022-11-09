
#include "inputRouter.h"

#include <iostream>

namespace citadel
{
    InputRouter::InputRouter()
    {

    }

    void InputRouter::BindToGLFW(GLFWwindow* window )
    {
        //Binding the inputRouter to the window, This must not be overwritten by anyone else or these
        glfwSetWindowUserPointer(window, this);
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto router = static_cast<InputRouter*>(glfwGetWindowUserPointer(window));
            auto itr = router->keyInputMap.find(key);
            if (itr != router->keyInputMap.end())
            {
                InputEventData eventData = KeyEvent(key, 
                                                    mods | GLFW_MOD_ALT, 
                                                    mods | GLFW_MOD_CONTROL, 
                                                    mods | GLFW_MOD_SHIFT, 
                                                    mods | GLFW_MOD_SUPER);
                auto keyCallback = itr->second;
                keyCallback(eventData);
                std::cout << "This is your key!!\n";
            }
            std::cout << "Key Callback" << std::endl << key << "," << scancode << "," << action << "," << mods << std::endl;
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
            auto router = static_cast<InputRouter*>(glfwGetWindowUserPointer(window));
            // std::cout << "MousePos Callback" << std::endl << "(" << x << ", " << y << ")" << std::endl;
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            auto router = static_cast<InputRouter*>(glfwGetWindowUserPointer(window));
            std::cout << "Click Callback" << std::endl << button << "," << action << "," << mods << std::endl;
        });
        glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
            auto router = static_cast<InputRouter*>(glfwGetWindowUserPointer(window));
            std::cout << "MouseScroll Callback" << std::endl << "(" << xoffset << ", " << yoffset << ")" << std::endl;
        });
    }

    void InputRouter::MapKey(int key, InputEventCallback callback)
    {
        if (keyInputMap.find(key) == keyInputMap.end())
        {
            keyInputMap[key] = callback;
        }
    }
}