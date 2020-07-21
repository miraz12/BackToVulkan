#ifndef _MESH_RESOURCE_H_
#define _MESH_RESOURCE_H_

#include "modelcontainers.h"



namespace Render
{
	class GraphicsPipeline;

	class MeshResource
	{
	public:
		MeshResource();
		~MeshResource();
		void BindBuffer(VkCommandBuffer commandBuffer);
		void LoadModel(std::string filename, GraphicsPipeline* pipe, float scale = 1.0f);
		void Draw(VkCommandBuffer commandBuffer);

		struct Vertices {
			VkBuffer buffer = VK_NULL_HANDLE;
			VkDeviceMemory memory;
		} vertices;
		struct Indices {
			int count;
			VkBuffer buffer = VK_NULL_HANDLE;
			VkDeviceMemory memory;
		} indices;

	private:
		void CreateVertexBuffer(std::vector<Vertex> vertexBuffer);
		void CreateIndexBuffer(std::vector<uint32_t> indexBuffer);

		GraphicsPipeline* pipeline;

		std::vector<Texture> textures;
		std::vector<TextureSampler> textureSamplers;
		std::vector<std::string> extensions;

	};
}

#endif // !_MESH_RESOURCE_H_
