#pragma once

class GLFWwindow;

namespace citadel {

class InputRouter {

public:
InputRouter();

void BindToGLFW(GLFWwindow* window);


};
    
}
