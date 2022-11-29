#include "shader.h"

#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>

namespace {
      std::vector<char> readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }
        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();

        return std::move(buffer);
    }
}

namespace citadel {

void Shader::CreateShaderModule(const std::vector<char>& code) 
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if (vkCreateShaderModule(m_device, &createInfo, nullptr, &module) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }

}

Shader::Shader(const VkDevice& device, std::string path) : m_device(device)
{
    CreateShaderModule(readFile(path));
}

Shader::~Shader()
{
    vkDestroyShaderModule(m_device, module, nullptr);
}

}