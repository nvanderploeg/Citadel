#pragma once
#include <optional>
#include <vector>
#include <string>
#include <memory>
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imageView.h"
#include "swapchain.h"
#include "vertex.h"
#include "meshData.h"
#include "swapchain.h"
#include "texture.h"

class GLFWwindow;

namespace citadel 
{
typedef std::function<void()> SwapChainRecreatedCallback;

struct UniformBufferObject 
{
    glm::mat4 view;
    glm::mat4 proj;
};

class GraphicsCore 
{
    friend class Renderer;
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
    std::vector<SwapChainRecreatedCallback> m_swapChainRecreatedCallbacks;
    uint32_t imageIndex;

    VkDescriptorSetLayout descriptorSetLayout;

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

    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    VkImage colorImage;
    VkDeviceMemory colorImageMemory;
    VkImageView colorImageView;

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
    void UpdateUniformBuffer(uint32_t currentImage, UniformBufferObject& ubo);
    void CreateDescriptorPool();

    void StartCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, VkRenderPass renderPass);

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
    
public:
    //Called to setup Vulkan for use
    static GraphicsCore* Instance();
    //Init wil set instance var.
    void Init(GLFWwindow* window);
    void Cleanup();

    MeshData Load(std::string modelPath, std::string texturePath);     
    
    BoundBuffer CreateVertexBuffer(const std::vector<Vertex>& verticies);
    BoundBuffer CreateIndexBuffer(const std::vector<uint32_t>& indices);

    Texture CreateTexture(std::string path);

    void HandleResize();

    void PrepareFrame();
    void EndFrame();

};

}