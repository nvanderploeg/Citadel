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
    glm::mat4 view;
    glm::mat4 proj;
};

struct BoundBuffer
{
    VkDevice device;
    VkBuffer buffer;
    VkDeviceMemory bufferMemory;
    ~BoundBuffer();
};

struct Texture
{
    bool valid = false;
    int mipLevels = -1;
    VkImage image;
    VkDeviceMemory imageMemory;
    VkImageView imageView;
    VkSampler sampler;

    //Is an array to hold one set per swapChain frame
    std::vector<VkDescriptorSet> descriptorSets;
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

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;
    VkDescriptorPool descriptorPool;

    Texture m_baseTexture;
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

    void CreateBuffer(VkDeviceSize size, 
                      VkBufferUsageFlags usage, 
                      VkMemoryPropertyFlags properties, 
                      VkBuffer& buffer, 
                      VkDeviceMemory& bufferMemory) const;

    void CreateUniformBuffers();
    void UpdateUniformBuffer(uint32_t currentImage);
    void CreateDescriptorPool();

    void StartCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void CreateImage(uint32_t width, 
                     uint32_t height, 
                     uint32_t mipLevels, 
                     VkSampleCountFlagBits numSamples, 
                     VkFormat format, 
                     VkImageTiling tiling, 
                     VkImageUsageFlags usage, 
                     VkMemoryPropertyFlags properties, 
                     VkImage& image, 
                     VkDeviceMemory& imageMemory) const;
                     
    // TODO: sort out global symbol shared with Swapchain
    // VkImageView CreateImageView(VkDevice device, 
    //                             VkImage image, 
    //                             VkFormat format, 
    //                             VkImageAspectFlags aspectFlags, 
    //                             uint32_t mipLevels) const;
    
    
    void CreateTextureImage(std::string path, Texture& _texture) const;
    void CreateTextureImageView(Texture& _texture) const;
    void CreateDescriptorSets(Texture& _texture) const;

    void CreateTextureSampler(Texture& _texture) const;
    void GenerateMipmaps(VkImage image, 
                         VkFormat imageFormat, 
                         int32_t texWidth, 
                         int32_t texHeight, 
                         uint32_t mipLevels) const;

    void CreateColorResources();
    void CreateDepthResources();

    VkCommandBuffer BeginSingleTimeCommands() const;
    void EndSingleTimeCommands(VkCommandBuffer commandBuffer) const;
    void TransitionImageLayout(VkImage image, 
                               VkFormat format, 
                               VkImageLayout oldLayout, 
                               VkImageLayout newLayout, 
                               uint32_t mipLevels) const;

    void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) const;

    //Helper Methods
    VkSampleCountFlagBits GetMaxUsableSampleCount() const;
    VkShaderModule CreateShaderModule(const std::vector<char>& code) const;
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;
    VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) const;
    VkFormat FindDepthFormat() const;

public:
    //Called to setup Vulkan for use
    static VulkanGraphics* Instance();
    void Init(GLFWwindow* window);

    MeshData Load(std::string modelPath, std::string texturePath);     
    
    BoundBuffer CreateVertexBuffer(const std::vector<Vertex>& verticies);
    BoundBuffer CreateIndexBuffer(const std::vector<uint32_t>& indices);

    Texture CreateTexture(std::string path);

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