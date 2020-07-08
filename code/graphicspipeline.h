#ifndef _GRAPHICS_PIPELINE_H_
#define _GRAPHICS_PIPELINE_H_

#include "shaderobject.h"
#include "vulkaninstance.h"
#include "graphicscomponent.h"

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
		VulkanInstance* vkInstance {nullptr};
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

		//Store this in ECS later
		GraphicsComponent* graphicsComp;
	};
}
#endif // !_GRAPHICS_PIPELINE_H_
