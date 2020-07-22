#include "textureresource.h"
#include "graphicspipeline.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION 
#include "tiny_gltf.h"

#include <stdexcept>

namespace Render
{
	TextureResource::TextureResource(GraphicsPipeline* pipeLine, const char* texfile)
	{
        this->pipeLine = pipeLine;
        CreateTextureImage(texfile);
        CreateTextureImageView();
        CreateTextureSampler();
	}
    TextureResource::~TextureResource()
    {
        vkDestroySampler(pipeLine->vkInstance->vDevice, textureSampler, nullptr);
        vkDestroyImageView(pipeLine->vkInstance->vDevice, textureImageView, nullptr);
        vkDestroyImage(pipeLine->vkInstance->vDevice, textureImage, nullptr);
        vkFreeMemory(pipeLine->vkInstance->vDevice, textureImageMemory, nullptr);
    }
    void TextureResource::CreateTextureImage(const char* texfile)
    {
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        int texWidth, texHeight, texChannels;
        stbi_uc* pixels = stbi_load(texfile, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        VkDeviceSize imageSize = texWidth * texHeight * 4;

        if (!pixels)
        {
            throw std::runtime_error("failed to load texture image!");
        }

        pipeLine->CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            stagingBuffer, stagingBufferMemory);
        void* data;
        vkMapMemory(pipeLine->vkInstance->vDevice, stagingBufferMemory, 0, imageSize, 0, &data);
        memcpy(data, pixels, static_cast<size_t>(imageSize));
        vkUnmapMemory(pipeLine->vkInstance->vDevice, stagingBufferMemory);

        stbi_image_free(pixels);

        pipeLine->CreateImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_SRGB,
 VK_IMAGE_TILING_OPTIMAL,
            VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 1, VK_SAMPLE_COUNT_1_BIT, textureImage, textureImageMemory);

        pipeLine->TransitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_SRGB, 1,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

        pipeLine->CopyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));

        pipeLine->TransitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

        vkDestroyBuffer(pipeLine->vkInstance->vDevice, stagingBuffer, nullptr);
        vkFreeMemory(pipeLine->vkInstance->vDevice, stagingBufferMemory, nullptr);
    }
    void TextureResource::CreateTextureImageView()
    {
        textureImageView = pipeLine->vkInstance->CreateImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, 1);
    }
    void TextureResource::CreateTextureSampler()
    {
        VkSamplerCreateInfo samplerInfo{};
        samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerInfo.magFilter = VK_FILTER_LINEAR;
        samplerInfo.minFilter = VK_FILTER_LINEAR;
        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.anisotropyEnable = VK_TRUE;
        samplerInfo.maxAnisotropy = 16.0f;
        samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        samplerInfo.unnormalizedCoordinates = VK_FALSE;
        samplerInfo.compareEnable = VK_FALSE;
        samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
        samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        samplerInfo.mipLodBias = 0.0f;
        samplerInfo.minLod = 0.0f;
        samplerInfo.maxLod = 0.0f;

        if (vkCreateSampler(pipeLine->vkInstance->vDevice, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create texture sampler!");
        }
    }
}