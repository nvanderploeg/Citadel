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

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    //Vulkan Device(GPU) setup
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;

    //Presentation
    VkSurfaceKHR surface;
    VkQueue presentQueue;

    //Creates and binds the instance
    void CreateInstance();
    //Scans Physical devices and picks one
    void PickPhysicalDevice();
    //Creates the logical device based on the physical one
    void CreateLogicalDevice();
    //Creates the surface binding (helped by GLFW)
    void CreateSurface(GLFWwindow* window);

    //Helper Methods
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities,GLFWwindow* window);

public:
    //Called to setup Vulkan for use
    void InitVulkan(GLFWwindow* window);

    //Called when we are all done with rendering
    void Cleanup();


};

}