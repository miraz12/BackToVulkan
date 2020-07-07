#ifndef _GRAPHICS_PIPELINE_H_
#define _GRAPHICS_PIPELINE_H_

#include "shaderobject.h"
#include "vulkaninstance.h"

namespace Render
{
	struct SwapChainVars;
	class GraphicsPipeline
	{
	public:
		GraphicsPipeline() {};
		GraphicsPipeline(VulkanInstance* vkInstance);
		~GraphicsPipeline();

		void DrawFrame();
		void RecreateSwapChain();
		void Cleanup();

	private:

		void CreateGraphicsPipeline();
		void CreateRenderPass();
		void CreateFramebuffers();
		void CreateCommandPool();
		void CreateCommandBuffers();
		void CreateSyncObjects();
		void CleanupSwapChain();

		//Vulkan instance
		VulkanInstance* vkInstance;
		//Vulkan pipeline layout
		VkPipelineLayout pipelineLayout;
		//Graphics pipeline
		VkPipeline graphicsPipeline;
		//Vulkan render pass
		VkRenderPass renderPass;
		//Vulkan swap chain framebuffers
		std::vector<VkFramebuffer> swapChainFramebuffers;
		//Vulkan command pool
		VkCommandPool commandPool;
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
		const int MAX_FRAMES_IN_FLIGHT = 2;
		//Current used fram
		size_t currentFrame = 0;
	};
}
#endif // !_GRAPHICS_PIPELINE_H_
