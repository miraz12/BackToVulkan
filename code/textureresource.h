#ifndef _TEXTURE_RESOURCE_H_
#define _TEXTURE_RESOURCE_H_

#include <vulkan/vulkan.h>

namespace Render
{
	class GraphicsPipeline;

	class TextureResource
	{
	public:
		TextureResource(GraphicsPipeline* pipeLine, const char* texfile);
		TextureResource() = default;
		~TextureResource();

		VkImage textureImage;
		VkDeviceMemory textureImageMemory;
		VkImageView textureImageView;
		VkSampler textureSampler;

	private:
		void CreateTextureImage(const char* texfile);
		void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout newLayout, VkImageLayout oldLayout = VK_IMAGE_LAYOUT_UNDEFINED);
		void CreateTextureImageView();
		void CreateTextureSampler();

		GraphicsPipeline* pipeLine;
	};
}

#endif // !_TEXTURE_RESOURCE_H_