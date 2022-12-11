#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>



namespace citadel 
{
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };


    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
    VkExtent2D chooseSwapExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);

    VkImageView CreateImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);


    struct SwapChain {
        VkSwapchainKHR swapChain;
        VkExtent2D extent;

        VkFormat imageFormat;
        std::vector<VkImage> images;
        std::vector<VkImageView> imageViews;

        static SwapChain Create(GLFWwindow* window, VkDevice _device, VkPhysicalDevice _physicalDevice, VkSurfaceKHR _surface);
    
    };
}