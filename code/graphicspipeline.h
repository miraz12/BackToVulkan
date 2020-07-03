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
		void Cleanup();

	private:

		void CreateRenderPass();
		void CreateFramebuffers();
		void CreateCommandPool();
		void CreateCommandBuffers();

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
	};
}
