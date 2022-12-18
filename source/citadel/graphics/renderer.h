#pragma once

#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "meshData.h"
#include "swapchain.h"

namespace citadel
{

class Renderer
{
    VkDevice device; 
    VkPhysicalDevice physicalDevice;
    VkCommandPool commandPool;

    uint32_t imageIndex;
    SwapChain swapChain;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

    void CreateRenderPass(VkSampleCountFlagBits samples);

    void StartCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

public:
    Renderer(VkDevice _device, VkPhysicalDevice _physicalDevice, VkCommandPool _commandPool);
    virtual ~Renderer();

    void BeginFrame();
    void Add(const RenderPayload& payload);
    void EndFrame();
};



}