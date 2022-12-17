#pragma once

#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "meshData.h"

namespace citadel
{

struct RenderPayload
{
    glm::mat4 model;
    MeshData meshData;
};


class Renderer
{

public:
    Renderer();
    virtual ~Renderer();


    void BeginFrame();
    void Add(const RenderPayload& payload);
    void EndFrame();
};



}