
#include "inputRouter.h"

#include <iostream>

#include "GLFW/glfw3.h"


namespace citadel {

InputRouter::InputRouter() {

}

void InputRouter::BindToGLFW(GLFWwindow* window ) {

    glfwSetKeyCallback(window, [](GLFWwindow* window,int key, int scancode, int action, int mods) {
        std::cout << "Key Callback" << std::endl << key << "," << scancode << "," << action << "," << mods << std::endl;
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window,double x, double y) {
        // std::cout << "MousePos Callback" << std::endl << x << " , " << y << std::endl;
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        std::cout << "Click Callback" << std::endl << button << "," << action << "," << mods << std::endl;
    });

}


}