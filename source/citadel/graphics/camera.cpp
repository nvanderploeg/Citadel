#include "camera.h"

namespace citadel
{

    glm::mat4 Camera::CalculateViewMatrix() const
    {
        return glm::lookAt(m_position, m_target, m_upVector);
    }

}
