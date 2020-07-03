#include "shaderobject.h"


namespace Render
{
	struct SwapChainVars;
	class VulkanInstance; 

	class GraphicsPipeline
	{
	public:
		GraphicsPipeline() {};
		GraphicsPipeline(VulkanInstance* vkInstance);
		~GraphicsPipeline();

	private:

		void CreateRenderPass();
		void CreateFramebuffers();
		void createCommandPool();

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
	};
}
