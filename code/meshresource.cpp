#include "meshresource.h"
#include "graphicspipeline.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace Render
{
	MeshResource::MeshResource()
	{
	}

	MeshResource::~MeshResource()
	{
		if (vertices.buffer != VK_NULL_HANDLE) 
		{
			vkDestroyBuffer(pipeline->vkInstance->vDevice, vertices.buffer, nullptr);
			vkFreeMemory(pipeline->vkInstance->vDevice, vertices.memory, nullptr);
		}
		if (indices.buffer != VK_NULL_HANDLE) 
		{
			vkDestroyBuffer(pipeline->vkInstance->vDevice, indices.buffer, nullptr);
			vkFreeMemory(pipeline->vkInstance->vDevice, indices.memory, nullptr);
		}
		for (auto texture : textures) 
		{
			vkDestroySampler(pipeline->vkInstance->vDevice, texture.sampler, nullptr);
			vkDestroyImageView(pipeline->vkInstance->vDevice, texture.view, nullptr);
			vkDestroyImage(pipeline->vkInstance->vDevice, texture.image, nullptr);
			vkFreeMemory(pipeline->vkInstance->vDevice, texture.deviceMemory, nullptr);
		}
		textures.resize(0);
		textureSamplers.resize(0);
		
		extensions.resize(0);
	}

	void MeshResource::BindBuffer(VkCommandBuffer commandBuffer)
	{
		VkBuffer vertexBuffers[] = { vertices.buffer };
		const VkDeviceSize offsets[] = { 0 };

		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		vkCmdBindIndexBuffer(commandBuffer, indices.buffer, 0, VK_INDEX_TYPE_UINT32);
	}

	void MeshResource::LoadModel(std::string filename, GraphicsPipeline* pipe, float scale)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		pipeline = pipe;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str())) 
		{
			throw std::runtime_error(warn + err);
		}

		std::vector<Vertex> vertexBuffer;
		std::vector<uint32_t> indexBuffer;

		for (const auto& shape : shapes) 
		{
			for (const auto& index : shape.mesh.indices) 
			{
				Vertex vertex{};

				vertex.pos = {
					attrib.vertices[3 * index.vertex_index + 0] * scale,
					attrib.vertices[3 * index.vertex_index + 1] * scale,
					attrib.vertices[3 * index.vertex_index + 2] * scale
				};

				vertex.normal = { 1.0f, 1.0f, 1.0f };

				vertex.UV = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					attrib.texcoords[2 * index.texcoord_index + 1]
				};

				vertexBuffer.push_back(vertex);
				indexBuffer.push_back(static_cast<uint32_t>(indexBuffer.size()));
			}
		}

		size_t vertexBufferSize = vertexBuffer.size() * sizeof(Vertex);
		indices.count = static_cast<uint32_t>(indexBuffer.size());

		assert(vertexBufferSize > 0);

		CreateVertexBuffer(vertexBuffer);
		CreateIndexBuffer(indexBuffer);
		
	}
	void MeshResource::Draw(VkCommandBuffer commandBuffer)
	{
		vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.count), 1, 0, 0, 0);
	}

	void Render::MeshResource::CreateVertexBuffer(std::vector<Vertex> vertexBuffer)
	{
		size_t vertexBufferSize = vertexBuffer.size() * sizeof(Vertex);

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		pipeline->CreateBuffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, 0, vertexBufferSize, 0, &data);
		memcpy(data, vertexBuffer.data(), (size_t)vertexBufferSize);
		vkUnmapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory);

		pipeline->CreateBuffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertices.buffer, vertices.memory);

		pipeline->CopyBuffer(stagingBuffer, vertices.buffer, vertexBufferSize);

		vkDestroyBuffer(pipeline->vkInstance->vDevice, stagingBuffer, nullptr);
		vkFreeMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, nullptr);
	}

	void Render::MeshResource::CreateIndexBuffer(std::vector<uint32_t> indexBuffer)
	{
		size_t indexBufferSize = indexBuffer.size() * sizeof(uint32_t);
		indices.count = static_cast<uint32_t>(indexBuffer.size());

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		pipeline->CreateBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, 0, indexBufferSize, 0, &data);
		memcpy(data, indexBuffer.data(), (size_t)indexBufferSize);
		vkUnmapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory);

		pipeline->CreateBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indices.buffer, indices.memory);

		pipeline->CopyBuffer(stagingBuffer, indices.buffer, indexBufferSize);

		vkDestroyBuffer(pipeline->vkInstance->vDevice, stagingBuffer, nullptr);
		vkFreeMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, nullptr);
	}
}

