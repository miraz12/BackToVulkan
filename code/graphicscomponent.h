#ifndef _GRAPHICS_COMPONENT_H_
#define _GRAPHICS_COMPONENT_H_
#include <vector>
#include <array>

#include "vulkaninstance.h"
#include "math/vector3D.h"
#include "math/vector2D.h"

namespace Render
{
	class GraphicsComponent
	{
	public:
		GraphicsComponent(VulkanInstance* vInstance);
		GraphicsComponent() = default;
		~GraphicsComponent();


		struct Vertex
		{
			Math::vector2D pos;
			Math::vector3D color;

			static VkVertexInputBindingDescription getBindingDescription() 
			{
				VkVertexInputBindingDescription bindingDescription{};
				bindingDescription.binding = 0;
				bindingDescription.stride = sizeof(Vertex);
				bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

				return bindingDescription;
			}

			static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
			{
				std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
				attributeDescriptions[0].binding = 0;
				attributeDescriptions[0].location = 0;
				attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
				attributeDescriptions[0].offset = offsetof(Vertex, pos);

				attributeDescriptions[1].binding = 0;
				attributeDescriptions[1].location = 1;
				attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
				attributeDescriptions[1].offset = offsetof(Vertex, color);
				
				return attributeDescriptions;
			}
		};

		const std::vector<Vertex> vertices = 
		{
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
		};

		VkBuffer vertexBuffer;


	private:
		void createVertexBuffer();

		VulkanInstance* vInstance;
		VkDeviceMemory vertexBufferMemory;

	};
}

#endif // !_GRAPHICS_COMPONENT_H_
