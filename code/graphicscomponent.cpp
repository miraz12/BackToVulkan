#include "graphicscomponent.h"
#include "graphicspipeline.h"

namespace Render
{
    GraphicsComponent::GraphicsComponent(GraphicsPipeline * vInstance) : pipeline(vInstance)
    {
        CreateTextureImage();
        CreateVertexBuffer();
        CreateIndexBuffer();
        mesh = new MeshResource();
        mesh->LoadModel("resources/models/Cube/Cube.gltf", vInstance, vInstance->vkInstance->graphicsQueue);
    }

    GraphicsComponent::~GraphicsComponent()
    {
        vkDestroyBuffer(pipeline->vkInstance->vDevice, vertexBuffer, nullptr);
        vkFreeMemory(pipeline->vkInstance->vDevice, vertexBufferMemory, nullptr);

        vkDestroyBuffer(pipeline->vkInstance->vDevice, indexBuffer, nullptr);
        vkFreeMemory(pipeline->vkInstance->vDevice, indexBufferMemory, nullptr);
        delete(texture);
    }

    void GraphicsComponent::CreateVertexBuffer()
    {
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        pipeline->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), (size_t)bufferSize);
        vkUnmapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory);

        pipeline->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

        pipeline->CopyBuffer(stagingBuffer, vertexBuffer, bufferSize);

        vkDestroyBuffer(pipeline->vkInstance->vDevice, stagingBuffer, nullptr);
        vkFreeMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, nullptr);
    }

    void GraphicsComponent::CreateIndexBuffer()
    {
        VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        pipeline->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, indices.data(), (size_t)bufferSize);
        vkUnmapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory);

        pipeline->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

        pipeline->CopyBuffer(stagingBuffer, indexBuffer, bufferSize);

        vkDestroyBuffer(pipeline->vkInstance->vDevice, stagingBuffer, nullptr);
        vkFreeMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, nullptr);
    }

    void GraphicsComponent::CreateTextureImage()
    {
        texture = new TextureResource(pipeline, "resources/textures/statue.jpg");
    }
}
