#include "renderer.h"
#include "formatSupport.h"

#include <vector>
#include <stdexcept>

namespace citadel
{

//  void Renderer::CreateRenderPass(VkSampleCountFlagBits samples)
// {
//     VkAttachmentDescription colorAttachment{};
//     colorAttachment.format = swapChain.imageFormat;
//     colorAttachment.samples = msaaSamples;
//     colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//     colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
//     colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//     colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//     colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//     colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

//     VkAttachmentDescription depthAttachment{};
//     depthAttachment.format = FindDepthFormat(physicalDevice);
//     depthAttachment.samples = msaaSamples;
//     depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//     depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//     depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//     depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//     depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//     depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

//     VkAttachmentDescription colorAttachmentResolve{};
//     colorAttachmentResolve.format = swapChain.imageFormat;
//     colorAttachmentResolve.samples = VK_SAMPLE_COUNT_1_BIT;
//     colorAttachmentResolve.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//     colorAttachmentResolve.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
//     colorAttachmentResolve.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//     colorAttachmentResolve.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//     colorAttachmentResolve.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//     colorAttachmentResolve.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;   

//     VkAttachmentReference colorAttachmentRef{};
//     colorAttachmentRef.attachment = 0;
//     colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

//     VkAttachmentReference depthAttachmentRef{};
//     depthAttachmentRef.attachment = 1;
//     depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

//     VkAttachmentReference colorAttachmentResolveRef{};
//     colorAttachmentResolveRef.attachment = 2;
//     colorAttachmentResolveRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

//     VkSubpassDescription subpass{};
//     subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
//     subpass.colorAttachmentCount = 1;
//     subpass.pColorAttachments = &colorAttachmentRef;
//     subpass.pDepthStencilAttachment = &depthAttachmentRef;
//     subpass.pResolveAttachments = &colorAttachmentResolveRef;

//     VkSubpassDependency dependency{};
//     dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
//     dependency.dstSubpass = 0;
//     dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
//     dependency.srcAccessMask = 0;
//     dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
//     dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

//     std::array<VkAttachmentDescription, 3> attachments = {colorAttachment, depthAttachment, colorAttachmentResolve};
//     VkRenderPassCreateInfo renderPassInfo{};
//     renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
//     renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
//     renderPassInfo.pAttachments = attachments.data();
//     renderPassInfo.subpassCount = 1;
//     renderPassInfo.pSubpasses = &subpass;
//     renderPassInfo.dependencyCount = 1;
//     renderPassInfo.pDependencies = &dependency;

//     if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
//         throw std::runtime_error("failed to create render pass!");
//     }
                                                 

//         UpdateUniformBuffer(currentFrame);

//         vkResetFences(device, 1, &inFlightFences[currentFrame]);

//         vkResetCommandBuffer(commandBuffers[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);

//         StartCommandBuffer(commandBuffers[currentFrame], imageIndex);

//     }


//     void Renderer::StartCommandBuffer(VkCommandBuffer commandBuffer, uint32_t _imageIndex)
//     {

//         // std::cout << "RecordCommandBuffer" << std::endl;
//         VkCommandBufferBeginInfo beginInfo{};
//         beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

//         if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
//             throw std::runtime_error("failed to begin recording command buffer!");
//         }

//         VkRenderPassBeginInfo renderPassInfo{};
//         renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
//         renderPassInfo.renderPass = renderPass;
//         renderPassInfo.framebuffer = swapChainFramebuffers[_imageIndex];
//         renderPassInfo.renderArea.offset = {0, 0};
//         renderPassInfo.renderArea.extent = swapChain.extent;
        
//         std::array<VkClearValue, 2> clearValues{};
//         clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
//         clearValues[1].depthStencil = {1.0f, 0};

//         renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
//         renderPassInfo.pClearValues = clearValues.data();

//         auto& extent = swapChain.extent;

//         vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

//             vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

//             VkViewport viewport{};
//             viewport.x = 0.0f;
//             viewport.y = 0.0f;
//             viewport.width = (float) extent.width;
//             viewport.height = (float) extent.height;
//             viewport.minDepth = 0.0f;
//             viewport.maxDepth = 1.0f;
//             vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
//             VkRect2D scissor{};
//             scissor.offset = {0, 0};
//             scissor.extent = extent;
//             vkCmdSetScissor(commandBuffer, 0, 1, &scissor);            
//     }
        
//     void Renderer::Add(const RenderPayload& payload)
//     {
//         // VkPipelineLayout                            layout,
//         // uint32_t                                    firstSet,
//         // uint32_t                                    descriptorSetCount,
//         // const VkDescriptorSet*                      pDescriptorSets,
//         // uint32_t                                    dynamicOffsetCount,
//         // const uint32_t*                             pDynamicOffsets);


//         if (payload.meshData.texture.valid) {
//             vkCmdBindDescriptorSets(commandBuffers[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, 
//             pipelineLayout, 0, 1, &payload.meshData.texture.descriptorSets[currentFrame], 0, nullptr);
//         }
//         else {
//             vkCmdBindDescriptorSets(commandBuffers[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, 
//             pipelineLayout, 0, 1, &m_baseTexture.descriptorSets[currentFrame], 0, nullptr);
//         }

//         //upload the model to the GPU via push constants
//         vkCmdPushConstants(commandBuffers[currentFrame], pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(payload.model), &payload.model);
     
//         VkBuffer vertexBuffers[] = {/*payload.vertexBuffer*/ payload.meshData.vertexBuffer.buffer};
//         VkDeviceSize offsets[] = {payload.meshData.offset};
//         vkCmdBindVertexBuffers(commandBuffers[currentFrame], 0, 1, vertexBuffers, offsets);

//         vkCmdBindIndexBuffer(commandBuffers[currentFrame], /*payload.indexBuffer*/payload.meshData.indexBuffer.buffer, 0, payload.meshData.indexBufferFormat);

//         vkCmdDrawIndexed(commandBuffers[currentFrame], payload.meshData.indexCount, 1, 0, 0, 0);
//     }

//     void Renderer::EndFrame()
//     {
//         vkCmdEndRenderPass(commandBuffers[currentFrame]);

//         if (vkEndCommandBuffer(commandBuffers[currentFrame]) != VK_SUCCESS) {
//             throw std::runtime_error("failed to record command buffer!");
//         }
        
//         VkSubmitInfo submitInfo{};
//         submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

//         VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
//         VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
//         submitInfo.waitSemaphoreCount = 1;
//         submitInfo.pWaitSemaphores = waitSemaphores;
//         submitInfo.pWaitDstStageMask = waitStages;

//         submitInfo.commandBufferCount = 1;
//         submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

//         VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
//         submitInfo.signalSemaphoreCount = 1;
//         submitInfo.pSignalSemaphores = signalSemaphores;

//         if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
//             throw std::runtime_error("failed to submit draw command buffer!");
//         }

//         VkPresentInfoKHR presentInfo{};
//         presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

//         presentInfo.waitSemaphoreCount = 1;
//         presentInfo.pWaitSemaphores = signalSemaphores;

//         VkSwapchainKHR swapChains[] = {swapChain.swapChain};
//         presentInfo.swapchainCount = 1;
//         presentInfo.pSwapchains = swapChains;

//         presentInfo.pImageIndices = &imageIndex;

//         auto result = vkQueuePresentKHR(presentQueue, &presentInfo);

//         if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
//             framebufferResized = false;
//             RecreateSwapChain();
//         } else if (result != VK_SUCCESS) {
//             throw std::runtime_error("failed to present swap chain image!");
//         }

//         currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
//     }

}