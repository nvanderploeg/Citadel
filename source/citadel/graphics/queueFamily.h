#pragma once

#include <optional>

#include <vulkan/vulkan.h>

namespace citadel
{
    
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice _device, VkSurfaceKHR _surface);

}