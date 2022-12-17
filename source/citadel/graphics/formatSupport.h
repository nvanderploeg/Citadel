#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace citadel
{

VkFormat FindSupportedFormat(VkPhysicalDevice _device, 
                             const std::vector<VkFormat>& candidates,
                             VkImageTiling tiling, 
                             VkFormatFeatureFlags features);
VkFormat FindDepthFormat(VkPhysicalDevice _device);

}
