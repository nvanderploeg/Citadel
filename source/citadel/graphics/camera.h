
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace citadel {

struct Camera {
    glm::vec3 m_position = {2, 2, 2};
    glm::vec3 m_target = {0, 0, 0};
    glm::vec3 m_upVector = {0, 0, 1};
    Camera() = default;
    virtual ~Camera() = default;
    virtual glm::mat4 CalculateViewMatrix() const;
};

}
