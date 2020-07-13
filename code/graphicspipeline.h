#ifndef _GRAPHICS_PIPELINE_H_
#define _GRAPHICS_PIPELINE_H_

#include "shaderobject.h"
#include "vulkaninstance.h"
#include "graphicscomponent.h"
#include "math/matrix4D.h"

namespace Render
{
	struct SwapChainVars;
	class GraphicsPipeline
	{
	public:

		GraphicsPipeline() = default;
		GraphicsPipeline(VulkanInstance* vkInstance);
		~GraphicsPipeline() = default;

		void DrawFrame();
		void RecreateSwapChain();
		void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		void Cleanup();

		//Vulkan instance
		VulkanInstance* vkInstance{ nullptr };

	private:

		void CreateDescriptorSetLayout();
		void CreateGraphicsPipeline();
		void CreateRenderPass();
		void CreateFramebuffers();
		void CreateCommandPool();
		void CreateCommandBuffers();
		void CreateSyncObjects();
		void CleanupSwapChain();
		void CreateUniformBuffers();
		void UpdateUniforms(uint32_t currentImage);
		void CreateDescriptorPool();
		void CreateDescriptorSets();

		//Vulkan pipeline layout
		VkPipelineLayout pipelineLayout{ VK_NULL_HANDLE };
		//Graphics pipeline
		VkPipeline graphicsPipeline{ VK_NULL_HANDLE };
		//Vulkan render pass
		VkRenderPass renderPass{ VK_NULL_HANDLE };
		//Vulkan swap chain framebuffers
		std::vector<VkFramebuffer> swapChainFramebuffers;
		//Vulkan command pool
		VkCommandPool commandPool{ VK_NULL_HANDLE };
		//Vulkan command buffers
		std::vector<VkCommandBuffer> commandBuffers;
		//Semaphores for syncing queues
		std::vector<VkSemaphore> imagesAvailable; //Waits for image to be avalible for drawing
		std::vector<VkSemaphore> rendersFinished; //Waits for swap presentation
		//Fance for syncing with GPU
		std::vector<VkFence> inFlight;
		//Track which images in swap chain are in flight
		std::vector<VkFence> imagesInFlight;
		//Maximum frames in flight
		const int MAX_FRAMES_IN_FLIGHT{ 2 };
		//Current used fram
		size_t currentFrame{ 0 };

		//Vulkan descriptor set layout
		VkDescriptorSetLayout descriptorSetLayout;
		//Vulkan descriptor set pool 
		VkDescriptorPool descriptorPool;
		//Vulkan descriptor sets
		std::vector<VkDescriptorSet> descriptorSets;

		//Store this in appropriate ECS component later
		GraphicsComponent* graphicsComp;
		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;

		struct UniformBufferObject {
			Math::matrix4D model; //TODO: This should be in graphics component
			Math::matrix4D view; //TODO: Theese two maybe in a "Camera" class or something
			Math::matrix4D proj;
		};
	};
}
#endif // !_GRAPHICS_PIPELINE_H_
