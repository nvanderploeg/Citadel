#pragma once

#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphicsCore.h"

namespace citadel
{

class Renderer
{
    GraphicsCore* m_graphics;

    // void StartCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

public:
    Renderer(GraphicsCore* graphics);
    virtual ~Renderer();

    void Prepare();
    void Add(const RenderPayload& payload);
    void Submit();
};



}