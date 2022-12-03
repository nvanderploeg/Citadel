
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace citadel {

class Camera {

    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_upVector;

   
public:
    Camera();

    glm::mat4 GetViewMatrix() const;
};


}