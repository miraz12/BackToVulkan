#include "meshresource.h"
#include "graphicspipeline.h"

namespace Render
{
	MeshResource::MeshResource()
	{
	}

	MeshResource::~MeshResource()
	{
	}

	void MeshResource::LoadModel(std::string filename, GraphicsPipeline* pipe, VkQueue transferQueue, float scale)
	{
		tinygltf::Model gltfModel;
		tinygltf::TinyGLTF gltfContext;
		std::string error;
		std::string warning;

		pipeline = pipe;

		bool binary = false;
		size_t extpos = filename.rfind('.', filename.length());
		if (extpos != std::string::npos) 
		{
			binary = (filename.substr(extpos + 1, filename.length() - extpos) == "glb");
		}

		bool fileLoaded = binary ? gltfContext.LoadBinaryFromFile(&gltfModel, &error, &warning, filename.c_str()) : gltfContext.LoadASCIIFromFile(&gltfModel, &error, &warning, filename.c_str());

		std::vector<uint32_t> indexBuffer;
		std::vector<Vertex> vertexBuffer;

		if (fileLoaded) 
		{
			LoadTextureSampler(gltfModel);
		}

	}
	void MeshResource::LoadTextureSampler(tinygltf::Model& gltfModel)
	{
		for (tinygltf::Sampler smpl : gltfModel.samplers) {
			TextureSampler sampler{};
			sampler.minFilter = GetVkFilterMode(smpl.minFilter);
			sampler.magFilter = GetVkFilterMode(smpl.magFilter);
			sampler.addressModeU = GetVkWrapMode(smpl.wrapS);
			sampler.addressModeV = GetVkWrapMode(smpl.wrapT);
			sampler.addressModeW = sampler.addressModeV;
			textureSamplers.push_back(sampler);
		}
	}
	VkFilter MeshResource::GetVkFilterMode(int32_t filterMode)
	{
		switch (filterMode) {
		case 9728:
			return VK_FILTER_NEAREST;
		case 9729:
			return VK_FILTER_LINEAR;
		case 9984:
			return VK_FILTER_NEAREST;
		case 9985:
			return VK_FILTER_NEAREST;
		case 9986:
			return VK_FILTER_LINEAR;
		case 9987:
			return VK_FILTER_LINEAR;
		}

		return VK_FILTER_NEAREST;
	}
	VkSamplerAddressMode MeshResource::GetVkWrapMode(int32_t wrapMode)
	{
		switch (wrapMode) 
		{
		case 10497:
			return VK_SAMPLER_ADDRESS_MODE_REPEAT;
		case 33071:
			return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		case 33648:
			return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		}
		return VK_SAMPLER_ADDRESS_MODE_REPEAT;
	}
	void MeshResource::LoadTextures(tinygltf::Model& gltfModel, VkQueue transferQueue)
	{
		for (tinygltf::Texture& tex : gltfModel.textures) {
			tinygltf::Image image = gltfModel.images[tex.source];
			TextureSampler textureSampler;
			if (tex.sampler == -1) {
				// No sampler specified, use a default one
				textureSampler.magFilter = VK_FILTER_LINEAR;
				textureSampler.minFilter = VK_FILTER_LINEAR;
				textureSampler.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				textureSampler.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				textureSampler.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			}
			else {
				textureSampler = textureSamplers[tex.sampler];
			}
			Texture texture;
//			CreateTextureImage(texture, image, textureSampler);
			textures.push_back(texture);
		}
	}
	void MeshResource::CreateTextureImage(Texture texture, tinygltf::Image& gltfimage, TextureSampler textureSampler)
	{
	}
}
