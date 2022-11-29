#pragma once

#include <string>
#include <vector>

#include <vulkan/vulkan.h>

namespace citadel {   

class Shader {
private:
void CreateShaderModule(const std::vector<char>& code);
VkDevice m_device;

public:
Shader(const VkDevice& device, std::string path);
~Shader();

VkShaderModule module;
};


    
}