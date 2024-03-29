#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>



namespace citadel 
{
    const int MAX_FRAMES_IN_FLIGHT = 2;

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };


    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
    VkExtent2D chooseSwapExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);

    struct SwapChain {
        VkSwapchainKHR swapChain;
        VkExtent2D extent;

        VkFormat imageFormat;
        std::vector<VkImage> images;
        std::vector<VkImageView> imageViews;
        std::vector<VkFramebuffer> framebuffers;
        
        static SwapChain Create(GLFWwindow* window, VkDevice _device, VkPhysicalDevice _physicalDevice, VkSurfaceKHR _surface);
    
    };
}