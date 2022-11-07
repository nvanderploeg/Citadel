#pragma once

#include "GLFW/glfw3.h"

namespace citadel
{
    class InputRouter
    {
    public:
        InputRouter();

        void BindToGLFW(GLFWwindow* window);
    };    
}
