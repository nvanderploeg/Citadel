
#include "inputRouter.h"

#include <iostream>

namespace citadel
{
    InputRouter::InputRouter()
    {

    }

    void InputRouter::BindToGLFW(GLFWwindow* window )
    {
        auto lambda = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            std::cout << "Key Callback" << std::endl << key << "," << scancode << "," << action << "," << mods << std::endl;
            auto self = static_cast<InputRouter*>(glfwGetWindowUserPointer(window));
            auto itr = self->keyInputMap.find(key);
            if (itr != self->keyInputMap.end())
            {
                inputEventData eventData = KeyEvent(key, false, false, false, false);
                itr->second(eventData);
                std::cout << "This is your key!!\n";
            }
        };
        glfwSetKeyCallback(window, lambda);

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
            std::cout << "MousePos Callback" << std::endl << "(" << x << ", " << y << ")" << std::endl;
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            std::cout << "Click Callback" << std::endl << button << "," << action << "," << mods << std::endl;
        });
        glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
            std::cout << "MouseScroll Callback" << std::endl << "(" << xoffset << ", " << yoffset << ")" << std::endl;
        });
    }

    void InputRouter::MapKey(int key, inputEventCallback callback)
    {
        if (keyInputMap.find(key) == keyInputMap.end())
        {
            keyInputMap[key] = callback;
        }
    }
}