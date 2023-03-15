
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace citadel {

struct Camera {
    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_upVector;
    Camera() = default;
    virtual ~Camera() = default;
    virtual glm::mat4 CalculateViewMatrix() const;
};

}
