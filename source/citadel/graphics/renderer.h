#pragma once

#include "graphicsCore.h"

namespace citadel
{

class Renderer
{
    GraphicsCore* m_graphics;

    VkRenderPass renderPass;
    // VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    std::vector<VkFramebuffer> framebuffers;
    SwapChainRecreatedCallback m_recreateCallback;

    void CreateRenderPass();
    void CreateGraphicsPipeline(const std::string& vertShader, const std::string& fragShader);
    void CreateFramebuffers();
    void CleanupFrameBuffers();

    UniformBufferObject m_ubo;
    float m_fieldOfViewDegrees = 45.0f;
    float m_cameraNearPlane = 5.0f;
    float m_cameraFarPlane = 100.f;

    void RecaluclateProjection();

    void StartCommandBuffer(VkCommandBuffer commandBuffer, uint32_t _imageIndex);

    void Init();
public:
    Renderer(GraphicsCore* graphics);
    virtual ~Renderer();

    void Prepare();
    void Add(const RenderPayload& payload);
    void Submit();

    void SetViewMatrix(glm::mat4 matrix);
    void SetFoV(float radians);
    void SetNearPlane(float nearPlane);
    void SetFarPlane(float farPlane);
};



}