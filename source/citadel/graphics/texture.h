#pragma once

#include <vector>

#include <vulkan/vulkan.h>

namespace citadel 
{

struct Texture
{
    bool valid = false;
    int mipLevels = -1;
    VkImage image;
    VkDeviceMemory imageMemory;
    VkImageView imageView;
    VkSampler sampler;

    //Is an array to, one set per swapChain frame 
    std::vector<VkDescriptorSet> descriptorSets;
};

}
