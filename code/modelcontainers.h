#ifndef _MODEL_CONTAINERS_H_
#define _MODEL_CONTAINERS_H_
#include "math/matrix4D.h"
#include "math/vector2D.h"


#include "tiny_gltf.h"

#include <vector>
#include <vulkan/vulkan.h>

#define MAX_NUM_JOINTS 128u

struct Node;

/*
	glTF texture sampler
*/
struct TextureSampler {
	VkFilter magFilter;
	VkFilter minFilter;
	VkSamplerAddressMode addressModeU;
	VkSamplerAddressMode addressModeV;
	VkSamplerAddressMode addressModeW;
};
/*
	glTF texture loading class
*/
struct Texture
{
	VkImage image;
	VkImageLayout imageLayout;
	VkDeviceMemory deviceMemory;
	VkImageView view;
	uint32_t width, height;
	uint32_t mipLevels;
	uint32_t layerCount;
	VkDescriptorImageInfo descriptor;
	VkSampler sampler;
};
/*
	glTF material class
*/
struct Material {
	enum AlphaMode { ALPHAMODE_OPAQUE, ALPHAMODE_MASK, ALPHAMODE_BLEND };
	AlphaMode alphaMode = ALPHAMODE_OPAQUE;
	float alphaCutoff = 1.0f;
	float metallicFactor = 1.0f;
	float roughnessFactor = 1.0f;
	Math::vector4D baseColorFactor = Math::vector4D(1.0f);
	Math::vector4D  emissiveFactor = Math::vector4D(1.0f);
	Texture* baseColorTexture;
	Texture* metallicRoughnessTexture;
	Texture* normalTexture;
	Texture* occlusionTexture;
	Texture* emissiveTexture;
	struct TexCoordSets {
		uint8_t baseColor = 0;
		uint8_t metallicRoughness = 0;
		uint8_t specularGlossiness = 0;
		uint8_t normal = 0;
		uint8_t occlusion = 0;
		uint8_t emissive = 0;
	} texCoordSets;
	struct Extension {
		Texture* specularGlossinessTexture;
		Texture* diffuseTexture;
		Math::vector4D diffuseFactor = Math::vector4D(1.0f);
		Math::vector3D specularFactor = Math::vector3D(0.0f);
	} extension;
	struct PbrWorkflows {
		bool metallicRoughness = true;
		bool specularGlossiness = false;
	} pbrWorkflows;
	VkDescriptorSet descriptorSet = VK_NULL_HANDLE;
};
/*
	glTF primitive
*/
struct Primitive {

	Primitive(uint32_t firstIndex, uint32_t indexCount, uint32_t vertexCount, Material& material) : firstIndex(firstIndex), indexCount(indexCount), vertexCount(vertexCount), material(material) {
		hasIndices = indexCount > 0;
	};
	uint32_t firstIndex;
	uint32_t indexCount;
	uint32_t vertexCount;
	Material& material;
	bool hasIndices;
};

/*
	glTF mesh
*/
struct Mesh {
	std::vector<Primitive*> primitives;

	Mesh()
	{};

	struct UniformBuffer {
		VkBuffer buffer;
		VkDeviceMemory memory;
		VkDescriptorBufferInfo descriptor;
		VkDescriptorSet descriptorSet;
		void* mapped;
	} uniformBuffer;

	struct UniformBlock {
		Math::matrix4D matrix;
	} uniformBlock;
};

/*
	glTF node
*/
struct Node {
	Node* parent;
	uint32_t index;
	std::vector<Node*> children;
	Math::matrix4D matrix;
	std::string name;
	Mesh mesh;
	Math::vector3D translation{};
	Math::vector3D scale{ 1.0f };
	Math::vector4D rotation{};
};

/*
	glTF model loading struct
*/
struct Vertex {
	Math::vector3D pos;
	Math::vector3D normal;
	Math::vector2D UV;

	static VkVertexInputBindingDescription getBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, normal);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, UV);

		return attributeDescriptions;
	}
};
#endif // !_MODEL_CONTAINERS_H_
