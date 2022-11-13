#pragma once
#include <optional>
#include <vector>
#include <vulkan/vulkan.h>

class GLFWwindow;

namespace citadel
{


struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;


    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class VulkanGraphics {

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
    //Swap chain
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;

    //Pipeline!
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    //Framebuffers
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;

    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
    VkFence inFlightFence;

    //Creates and binds the instance
    void CreateInstance();
    //Scans Physical devices and picks one
    void PickPhysicalDevice();
    //Creates the logical device based on the physical one
    void CreateLogicalDevice();
    //Creates the surface binding (helped by GLFW)
    void CreateSurface();

    void CreateSwapChain();
    void CreateImageViews(); 
    void CreateRenderPass();
    void CreateGraphicsPipeline();

    void CreateFramebuffers();
    void CreateCommandPool();
    void CreateCommandBuffer();

    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void CreateSyncObjects();

    //Helper Methods
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    VkShaderModule CreateShaderModule(const std::vector<char>& code);

public:
    //Called to setup Vulkan for use
    void InitVulkan(GLFWwindow* window);

    void DrawFrame();

    //Called when we are all done with rendering
    void Cleanup();


};

}