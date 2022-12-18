#pragma once

#include <glm/glm.hpp>

#include "texture.h"

namespace citadel
{

struct BoundBuffer
{
    VkDevice device;
    VkBuffer buffer;
    VkDeviceMemory bufferMemory;
    ~BoundBuffer();
};

struct MeshData
{
    BoundBuffer vertexBuffer;
    VkDeviceSize offset = 0;

    BoundBuffer indexBuffer;
    VkIndexType indexBufferFormat = VK_INDEX_TYPE_UINT32;
    uint32_t indexCount;

    Texture texture;
};

struct RenderPayload
{
    glm::mat4 model;
    MeshData meshData;
};

}