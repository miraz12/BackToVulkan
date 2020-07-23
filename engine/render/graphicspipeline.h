#ifndef _GRAPHICS_PIPELINE_H_
#define _GRAPHICS_PIPELINE_H_

#include "shaderobject.h"
#include "vulkaninstance.h"
#include "graphicscomponent.h"
#include "core/math/matrix4D.h"

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
		void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
						  VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		VkCommandBuffer BeginSingleTimeCommands();
		void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
		void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
		void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		void CreateImage(uint32_t width, uint32_t height, VkFormat format,
						VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
						uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkImage& image, VkDeviceMemory& imageMemory);

		void TransitionImageLayout(VkImage image, VkFormat format, uint32_t mipLevels, VkImageLayout newLayout,
								   VkImageLayout oldLayout = VK_IMAGE_LAYOUT_UNDEFINED);

		void GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);


		void Cleanup();


		//Vulkan instance
		VulkanInstance* vkInstance{ nullptr };
		//Vulkan pipeline layout
		VkPipelineLayout pipelineLayout{ VK_NULL_HANDLE };

		//Store this in appropriate ECS component later
		GraphicsComponent* graphicsComp;

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
		void CreateDepthResources();
		void CreateColorResources();
		
		VkFormat FindDepthFormat();
		bool HasStencilComponent(VkFormat format);
		


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
		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;

		//MSAA
		VkImage colorImage;
		VkDeviceMemory colorImageMemory;
		VkImageView colorImageView;

		//Vulkan depth variables
		VkImage depthImage;
		VkDeviceMemory depthImageMemory;
		VkImageView depthImageView;

		struct UniformBufferObject {
			Math::matrix4D model; //TODO: This should be in graphics component
			Math::matrix4D view; //TODO: Theese two maybe in a "Camera" class or something
			Math::matrix4D proj;
		};
	};
}
#endif // !_GRAPHICS_PIPELINE_H_
