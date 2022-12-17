#pragma once

#include <vulkan/vulkan.h>

namespace citadel
{


VkImageView CreateImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);



}