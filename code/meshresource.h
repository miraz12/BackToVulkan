#ifndef _MESH_RESOURCE_H_
#define _MESH_RESOURCE_H_

#include "modelcontainers.h"



namespace Render
{
	class GraphicsPipeline;
	class GraphicsComponent;

	class MeshResource
	{
	public:
		MeshResource();
		~MeshResource();
		void BindBuffer(VkCommandBuffer commandBuffer);
		void LoadModel(std::string filename, GraphicsPipeline* pipe, float scale = 1.0f);
		void Draw(VkCommandBuffer commandBuffer);

	private:
		void LoadTextureSampler(tinygltf::Model& gltfModel);
		VkFilter GetVkFilterMode(int32_t filterMode);
		VkSamplerAddressMode GetVkWrapMode(int32_t wrapMode);
		void LoadTextures(tinygltf::Model& gltfModel);
		void CreateTextureImage(Texture* texture, tinygltf::Image& gltfimage, TextureSampler textureSampler);
		void LoadMaterials(tinygltf::Model& gltfModel);
		void LoadNode(Node* parent, tinygltf::Node& node, uint32_t nodeIndex, tinygltf::Model& model, std::vector<uint32_t>& indexBuffer, std::vector<Vertex>& vertexBuffer, float globalscale);
		void DrawNode(Node* node, VkCommandBuffer commandBuffer);
		
		
		void CreateVertexBuffer(std::vector<Vertex> vertexBuffer);
		void CreateIndexBuffer(std::vector<uint32_t> indexBuffer);

		GraphicsPipeline* pipeline{nullptr};
		GraphicsComponent* gComp{ nullptr };

	public:
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
