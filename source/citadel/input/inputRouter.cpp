
#include "inputRouter.h"

#include <iostream>

namespace citadel
{
    InputRouter::InputRouter()
    {

    }

    void InputRouter::BindToGLFW(GLFWwindow* window)
    {
        // NOTE: Binding the inputRouter to the window.
        // This must not be overwritten by anyone else or these callbacks won't work.
        glfwSetWindowUserPointer(window, this);

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            // Grab a reference to ourselves from the window; set previously, above.
            InputRouter * router = static_cast<InputRouter*>(glfwGetWindowUserPointer(window));

            KeyEvent keyEvent = { key, action, mods };

            // If there is a key mapping for this key, call it's callback.
            auto itr = router->keyInputMap.find(keyEvent);
            if (itr != router->keyInputMap.end())
            {
                InputEventData eventData = KeyEventData(key, 
                                                    mods | GLFW_MOD_ALT, 
                                                    mods | GLFW_MOD_CONTROL, 
                                                    mods | GLFW_MOD_SHIFT, 
                                                    mods | GLFW_MOD_SUPER);
                InputEventCallback keyCallback = itr->second;
                keyCallback(eventData);
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

    void InputRouter::MapKey(KeyEvent keyEvent, InputEventCallback callback)
    {
        if (keyInputMap.find(keyEvent) == keyInputMap.end())
        {
            keyInputMap[keyEvent] = callback;
        }
    }
}