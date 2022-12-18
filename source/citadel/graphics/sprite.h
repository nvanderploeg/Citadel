#pragma once

#include <glm/glm.hpp>

#include "meshData.h"

namespace citadel
{

class Sprite
{
    bool m_static;
    glm::vec3 position;
    glm::vec3 scale;
public:
    Sprite() = default;
    virtual ~Sprite();
    
    RenderPayload GetRenderPayload();
};

}