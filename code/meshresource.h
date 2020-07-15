#ifndef _MESH_RESOURCE_H_
#define _MESH_RESOURCE_H_

#include "modelcontainers.h"



namespace Render
{
	// Changing this value here also requires changing it in the vertex shader

	class GraphicsPipeline;

	class MeshResource
	{
	public:
		MeshResource();
		~MeshResource();
		void LoadModel(std::string filename, GraphicsPipeline* pipe, VkQueue transferQueue, float scale = 1.0f);

	private:
		void LoadTextureSampler(tinygltf::Model& gltfModel);
		VkFilter GetVkFilterMode(int32_t filterMode);
		VkSamplerAddressMode GetVkWrapMode(int32_t wrapMode);
		void LoadTextures(tinygltf::Model& gltfModel, VkQueue transferQueue);
		void CreateTextureImage(Texture texture, tinygltf::Image& gltfimage, TextureSampler textureSampler);

		GraphicsPipeline* pipeline;

		struct Vertices {
			VkBuffer buffer = VK_NULL_HANDLE;
			VkDeviceMemory memory;
		} vertices;
		struct Indices {
			int count;
			VkBuffer buffer = VK_NULL_HANDLE;
			VkDeviceMemory memory;
		} indices;

		std::vector<Node*> nodes;
		std::vector<Node*> linearNodes;

		std::vector<Texture> textures;
		std::vector<TextureSampler> textureSamplers;
		std::vector<Material> materials;
		std::vector<std::string> extensions;

		struct Dimensions {
			Math::vector3D min = Math::vector3D(FLT_MAX);
			Math::vector3D max = Math::vector3D(-FLT_MAX);
		} dimensions;
	};
}

#endif // !_MESH_RESOURCE_H_
