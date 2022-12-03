#include "camera.h"

namespace citadel {

    Camera::Camera() {
        m_position = {2.0f, 2.0f, 2.0f};
        m_target = {0.f, 0.f, 0.f};
        m_upVector = {0.f, 0.f, 1.0f};
    }

    glm::mat4 Camera::GetViewMatrix() const {
        return glm::lookAt(m_position, m_target, m_upVector);
    }


}