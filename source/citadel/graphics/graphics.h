#pragma once
#include <optional>
#include <vector>
#include <string>
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "swapchain.h"
#include "vertex.h"

class GLFWwindow;

namespace citadel 
{

struct UniformBufferObject 
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

struct RenderPayload
{
    VkBuffer vertexBuffer;
    VkDeviceSize offset = 0;
    VkBuffer indexBuffer;
    
    VkIndexType indexBufferFormat = VK_INDEX_TYPE_UINT32;
    VkDescriptorSet descriptorSet;
};

class VulkanGraphics 
{
    GLFWwindow* window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    //Vulkan Device(GPU) setup
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;

    //Presentation
    VkSurfaceKHR surface;
    VkQueue presentQueue;

    SwapChain swapChain;
    uint32_t imageIndex;

    //Pipeline!
    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    //Framebuffers
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkCommandPool commandPool;
    
    uint32_t currentFrame = 0;
    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    std::vector<Vertex> vertices;

    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    std::vector<uint32_t> indices;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;


    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    uint32_t m_mipLevels;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    VkImage colorImage;
    VkDeviceMemory colorImageMemory;
    VkImageView colorImageView;

    bool framebufferResized = false;

    UniformBufferObject m_ubo;

    //Basic setup

    void SetupDebugMessenger();
    void CreateInstance();
    void PickPhysicalDevice();
    void CreateLogicalDevice();
    void CreateSurface();

    //Setup pipeline
    void CreateRenderPass();
    void CreateDescriptorSetLayout();
    VkPipeline CreateGraphicsPipeline(const VkDevice device, const std::string& vertShader, const std::string& fragShader, const VkSampleCountFlagBits aaSamples = VK_SAMPLE_COUNT_1_BIT);

    //Setup swapchains
    void CleanupSwapChain();
    void RecreateSwapChain();

    void CreateFramebuffers();
    void CreateCommandPool();
    void CreateCommandBuffers();
    void CreateSyncObjects();

    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void CreateVertexBuffer();
    void CreateIndexBuffer();

    void CreateUniformBuffers();
    void UpdateUniformBuffer(uint32_t currentImage);
    void CreateDescriptorPool();
    void CreateDescriptorSets();

    void StartCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void CreateImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void CreateTextureImage(std::string path);

    
    void CreateTextureImageView();
    void CreateTextureSampler();
    void GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

    void LoadModel(std::string path);

    void CreateColorResources();
    void CreateDepthResources();

    VkCommandBuffer BeginSingleTimeCommands();
    void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
    void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
    void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    //Helper Methods
    VkSampleCountFlagBits GetMaxUsableSampleCount();
    VkShaderModule CreateShaderModule(const std::vector<char>& code);
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat FindDepthFormat();
public:
    //Called to setup Vulkan for use
    void Init(GLFWwindow* window);

    void HandleResize();
    void StartDraw();
    void AddToDraw(const RenderPayload& payload);
    void SubmitDraw();

    void SetViewMatrix(glm::mat4 matrix);
    void SetFoV(float radians);

    //Called when we are all done with rendering
    void Cleanup();
};

}