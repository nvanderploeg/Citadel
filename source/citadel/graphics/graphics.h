#pragma once
#include <optional>
#include <vulkan/vulkan.h>

namespace citadel
{


struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

class VulkanGraphics {

    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    
    //Creates and binds the instance
    void CreateInstance();
    //Scans Physical devices and picks one
    void PickPhysicalDevice();
    //Creates the logical device based on the physical one
    void CreateLogicalDevice();
public:
    //Called to setup Vulkan for use
    void InitVulkan();

    //Called when we are all done with rendering
    void Cleanup();


};

}