//#include "meshresource.h"
//#include "graphicspipeline.h"
//#include "math/quaternion.h"
//
//namespace Render
//{
//	MeshResource::MeshResource()
//	{
//	}
//
//	MeshResource::~MeshResource()
//	{
//		if (vertices.buffer != VK_NULL_HANDLE) 
//		{
//			vkDestroyBuffer(pipeline->vkInstance->vDevice, vertices.buffer, nullptr);
//			vkFreeMemory(pipeline->vkInstance->vDevice, vertices.memory, nullptr);
//		}
//		if (indices.buffer != VK_NULL_HANDLE) 
//		{
//			vkDestroyBuffer(pipeline->vkInstance->vDevice, indices.buffer, nullptr);
//			vkFreeMemory(pipeline->vkInstance->vDevice, indices.memory, nullptr);
//		}
//		for (auto texture : textures) 
//		{
//			vkDestroySampler(pipeline->vkInstance->vDevice, texture.sampler, nullptr);
//			vkDestroyImageView(pipeline->vkInstance->vDevice, texture.view, nullptr);
//			vkDestroyImage(pipeline->vkInstance->vDevice, texture.image, nullptr);
//			vkFreeMemory(pipeline->vkInstance->vDevice, texture.deviceMemory, nullptr);
//		}
//		textures.resize(0);
//		textureSamplers.resize(0);
//		for (auto node : nodes) 
//		{
//			vkDestroyBuffer(pipeline->vkInstance->vDevice, node->mesh.uniformBuffer.buffer, nullptr);
//			vkFreeMemory(pipeline->vkInstance->vDevice, node->mesh.uniformBuffer.memory, nullptr);
//			for (Primitive* p : node->mesh.primitives)
//			{
//				delete p;
//			}
//		}
//		materials.resize(0);
//		nodes.resize(0);
//		linearNodes.resize(0);
//		extensions.resize(0);
//	}
//
//	void MeshResource::BindBuffer(VkCommandBuffer commandBuffer)
//	{
//		VkBuffer vertexBuffers[] = { vertices.buffer };
//		const VkDeviceSize offsets[] = { 0 };
//
//		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
//		vkCmdBindIndexBuffer(commandBuffer, indices.buffer, 0, VK_INDEX_TYPE_UINT32);
//	}
//
//	void MeshResource::LoadModel(std::string filename, GraphicsPipeline* pipe, float scale)
//	{
//		tinygltf::Model gltfModel;
//		tinygltf::TinyGLTF gltfContext;
//		std::string error;
//		std::string warning;
//
//		pipeline = pipe;
//
//		bool binary = false;
//		size_t extpos = filename.rfind('.', filename.length());
//		if (extpos != std::string::npos) 
//		{
//			binary = (filename.substr(extpos + 1, filename.length() - extpos) == "glb");
//		}
//
//		bool fileLoaded = binary ? gltfContext.LoadBinaryFromFile(&gltfModel, &error, &warning, filename.c_str()) : gltfContext.LoadASCIIFromFile(&gltfModel, &error, &warning, filename.c_str());
//
//		std::vector<uint32_t> indexBuffer;
//		std::vector<Vertex> vertexBuffer;
//
//		if (fileLoaded) 
//		{
//			LoadTextureSampler(gltfModel);
//			LoadTextures(gltfModel);
//			LoadMaterials(gltfModel);
//			// TODO: scene handling with no default scene
//			const tinygltf::Scene& scene = gltfModel.scenes[gltfModel.defaultScene > -1 ? gltfModel.defaultScene : 0];
//			for (size_t i = 0; i < scene.nodes.size(); i++) {
//				const tinygltf::Node node = gltfModel.nodes[scene.nodes[i]];
//				LoadNode(nullptr, node, scene.nodes[i], gltfModel, indexBuffer, vertexBuffer, scale);
//			}
//		}
//		else {
//			// TODO: throw
//			std::cerr << "Could not load gltf file: " << error << std::endl;
//			return;
//		}
//
//		extensions = gltfModel.extensionsUsed;
//
//		size_t vertexBufferSize = vertexBuffer.size() * sizeof(Vertex);
//		size_t indexBufferSize = indexBuffer.size() * sizeof(uint32_t);
//		indices.count = static_cast<uint32_t>(indexBuffer.size());
//
//		assert(vertexBufferSize > 0);
//
//		CreateVertexBuffer(vertexBuffer);
//		CreateIndexBuffer(indexBuffer);
//		
//	}
//	void MeshResource::Draw(VkCommandBuffer commandBuffer)
//	{
//		const VkDeviceSize offsets[1] = { 0 };
//		vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertices.buffer, offsets);
//		vkCmdBindIndexBuffer(commandBuffer, indices.buffer, 0, VK_INDEX_TYPE_UINT32);
//		
//		for (auto& node : nodes) 
//		{
//			DrawNode(node, commandBuffer);
//		}
//	}
//
//	void MeshResource::LoadTextureSampler(tinygltf::Model& gltfModel)
//	{
//		for (tinygltf::Sampler smpl : gltfModel.samplers) {
//			TextureSampler sampler{};
//			sampler.minFilter = GetVkFilterMode(smpl.minFilter); 
//			sampler.magFilter = GetVkFilterMode(smpl.magFilter);
//			sampler.addressModeU = GetVkWrapMode(smpl.wrapS);
//			sampler.addressModeV = GetVkWrapMode(smpl.wrapT);
//			sampler.addressModeW = sampler.addressModeV;
//			textureSamplers.push_back(sampler);
//		}
//	}
//	VkFilter MeshResource::GetVkFilterMode(int32_t filterMode)
//	{
//		switch (filterMode) {
//		case 9728:
//			return VK_FILTER_NEAREST;
//		case 9729:
//			return VK_FILTER_LINEAR;
//		case 9984:
//			return VK_FILTER_NEAREST;
//		case 9985:
//			return VK_FILTER_NEAREST;
//		case 9986:
//			return VK_FILTER_LINEAR;
//		case 9987:
//			return VK_FILTER_LINEAR;
//		}
//
//		return VK_FILTER_NEAREST;
//	}
//	VkSamplerAddressMode MeshResource::GetVkWrapMode(int32_t wrapMode)
//	{
//		switch (wrapMode) 
//		{
//		case 10497:
//			return VK_SAMPLER_ADDRESS_MODE_REPEAT;
//		case 33071:
//			return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
//		case 33648:
//			return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
//		}
//		return VK_SAMPLER_ADDRESS_MODE_REPEAT;
//	}
//	void MeshResource::LoadTextures(tinygltf::Model& gltfModel)
//	{
//		for (tinygltf::Texture& tex : gltfModel.textures) {
//			tinygltf::Image image = gltfModel.images[tex.source];
//			TextureSampler textureSampler;
//			if (tex.sampler == -1) {
//				// No sampler specified, use a default one
//				textureSampler.magFilter = VK_FILTER_LINEAR;
//				textureSampler.minFilter = VK_FILTER_LINEAR;
//				textureSampler.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
//				textureSampler.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
//				textureSampler.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
//			}
//			else {
//				textureSampler = textureSamplers[tex.sampler];
//			}
//			Texture texture{0};
//			CreateTextureImage(&texture, image, textureSampler);
//			textures.push_back(texture);
//		}
//	}
//	void MeshResource::CreateTextureImage(Texture* texture, tinygltf::Image& gltfimage, TextureSampler textureSampler)
//	{
//		unsigned char* buffer = nullptr;
//		VkDeviceSize bufferSize = 0;
//		bool deleteBuffer = false;
//		if (gltfimage.component == 3) 
//		{
//			// Most devices don't support RGB only on Vulkan so convert if necessary
//			// TODO: Check actual format support and transform only if required
//			bufferSize = gltfimage.width * gltfimage.height * 4;
//			buffer = new unsigned char[bufferSize]; 
//			unsigned char* rgba = buffer;
//			unsigned char* rgb = &gltfimage.image[0];
//			for (int32_t i = 0; i < gltfimage.width * gltfimage.height; ++i) 
//			{
//				for (int32_t j = 0; j < 3; ++j) 
//				{
//					rgba[j] = rgb[j];
//				}
//				rgba += 4;
//				rgb += 3;
//			}
//			deleteBuffer = true;
//		}
//		else 
//		{
//			buffer = &gltfimage.image[0];
//			bufferSize = gltfimage.image.size();
//		}
//
//		//Create texture image
//		VkBuffer stagingBuffer;
//		VkDeviceMemory stagingBufferMemory;
//
//		VkFormat format = VK_FORMAT_R8G8B8A8_UNORM;
//		texture->width = gltfimage.width;
//		texture->height = gltfimage.height;
//		texture->mipLevels = 0;// static_cast<uint32_t>(floor(log2(std::max(texture->width, texture->height))) + 1.0);
//
//		pipeline->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
//			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
//			stagingBuffer, stagingBufferMemory);
//		void* data;
//		vkMapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
//		memcpy(data, buffer, static_cast<size_t>(bufferSize));
//		vkUnmapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory);
//
//		pipeline->CreateImage(texture->width, texture->height, format, VK_IMAGE_TILING_OPTIMAL,
//			VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 
//			texture->image, texture->deviceMemory);
//
//		pipeline->TransitionImageLayout(texture->image, format,
//			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
//
//		pipeline->CopyBufferToImage(stagingBuffer, texture->image, static_cast<uint32_t>(texture->width), static_cast<uint32_t>(texture->height));
//
//		pipeline->TransitionImageLayout(texture->image, format, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
//
//		vkDestroyBuffer(pipeline->vkInstance->vDevice, stagingBuffer, nullptr);
//		vkFreeMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, nullptr);
//
//		texture->imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//
//		//Create texture sampler
//		VkSamplerCreateInfo samplerInfo{};
//		samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
//		samplerInfo.magFilter = textureSampler.magFilter;
//		samplerInfo.minFilter = textureSampler.minFilter;
//		samplerInfo.addressModeU = textureSampler.addressModeU;
//		samplerInfo.addressModeV = textureSampler.addressModeV;
//		samplerInfo.addressModeW = textureSampler.addressModeW;
//		samplerInfo.anisotropyEnable = VK_TRUE;
//		samplerInfo.maxAnisotropy = 16.0f;
//		samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
//		samplerInfo.unnormalizedCoordinates = VK_FALSE;
//		samplerInfo.compareEnable = VK_FALSE;
//		samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
//		samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
//		samplerInfo.mipLodBias = 0.0f;
//		samplerInfo.minLod = 0.0f;
//		samplerInfo.maxLod = 0.0f;
//
//		if (vkCreateSampler(pipeline->vkInstance->vDevice, &samplerInfo, nullptr, &texture->sampler) != VK_SUCCESS)
//		{
//			throw std::runtime_error("failed to create texture sampler!");
//		}
//
//		//Create image view
//		texture->view = pipeline->vkInstance->CreateImageView(texture->image, format, VK_IMAGE_ASPECT_COLOR_BIT);
//		texture->descriptor.imageView = texture->view;
//		texture->descriptor.sampler = texture->sampler;
//		texture->descriptor.imageLayout = texture->imageLayout;
//
//		if (deleteBuffer)
//			delete[] buffer;
//
//		return;
//	}
//	void MeshResource::LoadMaterials(tinygltf::Model& gltfModel)
//	{
//		for (tinygltf::Material& mat : gltfModel.materials) {
//			Material material{};
//			if (mat.values.find("baseColorTexture") != mat.values.end()) {
//				material.baseColorTexture = &textures[mat.values["baseColorTexture"].TextureIndex()];
//				material.texCoordSets.baseColor = static_cast<uint8_t>(mat.values["baseColorTexture"].TextureTexCoord());
//			}
//			if (mat.values.find("metallicRoughnessTexture") != mat.values.end()) {
//				material.metallicRoughnessTexture = &textures[mat.values["metallicRoughnessTexture"].TextureIndex()];
//				material.texCoordSets.metallicRoughness = static_cast<uint8_t>(mat.values["metallicRoughnessTexture"].TextureTexCoord());
//			}
//			if (mat.values.find("roughnessFactor") != mat.values.end()) {
//				material.roughnessFactor = static_cast<float>(mat.values["roughnessFactor"].Factor());
//			}
//			if (mat.values.find("metallicFactor") != mat.values.end()) {
//				material.metallicFactor = static_cast<float>(mat.values["metallicFactor"].Factor());
//			}
//			if (mat.values.find("baseColorFactor") != mat.values.end()) {
//				material.baseColorFactor = Math::vector4D(*mat.values["baseColorFactor"].ColorFactor().data());
//			}
//			if (mat.additionalValues.find("normalTexture") != mat.additionalValues.end()) {
//				material.normalTexture = &textures[mat.additionalValues["normalTexture"].TextureIndex()];
//				material.texCoordSets.normal = static_cast<uint8_t>(mat.additionalValues["normalTexture"].TextureTexCoord());
//			}
//			if (mat.additionalValues.find("emissiveTexture") != mat.additionalValues.end()) {
//				material.emissiveTexture = &textures[mat.additionalValues["emissiveTexture"].TextureIndex()];
//				material.texCoordSets.emissive = static_cast<uint8_t>(mat.additionalValues["emissiveTexture"].TextureTexCoord());
//			}
//			if (mat.additionalValues.find("occlusionTexture") != mat.additionalValues.end()) {
//				material.occlusionTexture = &textures[mat.additionalValues["occlusionTexture"].TextureIndex()];
//				material.texCoordSets.occlusion = static_cast<uint8_t>(mat.additionalValues["occlusionTexture"].TextureTexCoord());
//			}
//			if (mat.additionalValues.find("alphaMode") != mat.additionalValues.end()) {
//				tinygltf::Parameter param = mat.additionalValues["alphaMode"];
//				if (param.string_value == "BLEND") {
//					material.alphaMode = Material::ALPHAMODE_BLEND;
//				}
//				if (param.string_value == "MASK") {
//					material.alphaCutoff = 0.5f;
//					material.alphaMode = Material::ALPHAMODE_MASK;
//				}
//			}
//			if (mat.additionalValues.find("alphaCutoff") != mat.additionalValues.end()) {
//				material.alphaCutoff = static_cast<float>(mat.additionalValues["alphaCutoff"].Factor());
//			}
//			if (mat.additionalValues.find("emissiveFactor") != mat.additionalValues.end()) {
//				material.emissiveFactor = Math::vector4D(Math::vector3D(*mat.additionalValues["emissiveFactor"].ColorFactor().data()), 1.0);
//				material.emissiveFactor = Math::vector4D(0.0f);
//			}
//
//			// Extensions
//			// @TODO: Find out if there is a nicer way of reading these properties with recent tinygltf headers
//			if (mat.extensions.find("KHR_materials_pbrSpecularGlossiness") != mat.extensions.end()) {
//				auto ext = mat.extensions.find("KHR_materials_pbrSpecularGlossiness");
//				if (ext->second.Has("specularGlossinessTexture")) {
//					auto index = ext->second.Get("specularGlossinessTexture").Get("index");
//					material.extension.specularGlossinessTexture = &textures[index.Get<int>()];
//					auto texCoordSet = ext->second.Get("specularGlossinessTexture").Get("texCoord");
//					material.texCoordSets.specularGlossiness = static_cast<uint8_t>(texCoordSet.Get<int>());
//					material.pbrWorkflows.specularGlossiness = true;
//				}
//				if (ext->second.Has("diffuseTexture")) {
//					auto index = ext->second.Get("diffuseTexture").Get("index");
//					material.extension.diffuseTexture = &textures[index.Get<int>()];
//				}
//				if (ext->second.Has("diffuseFactor")) {
//					auto factor = ext->second.Get("diffuseFactor");
//					for (uint32_t i = 0; i < factor.ArrayLen(); i++) {
//						auto val = factor.Get(i);
//						material.extension.diffuseFactor[i] = val.IsNumber() ? (float)val.Get<double>() : (float)val.Get<int>();
//					}
//				}
//				if (ext->second.Has("specularFactor")) {
//					auto factor = ext->second.Get("specularFactor");
//					for (uint32_t i = 0; i < factor.ArrayLen(); i++) {
//						auto val = factor.Get(i);
//						material.extension.specularFactor[i] = val.IsNumber() ? (float)val.Get<double>() : (float)val.Get<int>();
//					}
//				}
//			}
//
//			materials.push_back(material);
//		}
//		// Push a default material at the end of the list for meshes with no material assigned
//		materials.push_back(Material());
//	}
//	void MeshResource::LoadNode(Node* parent, const tinygltf::Node& node, uint32_t nodeIndex, const tinygltf::Model& model, std::vector<uint32_t>& indexBuffer, std::vector<Vertex>& vertexBuffer, float globalscale)
//	{
//		Node* newNode = new Node{};
//		newNode->index = nodeIndex;
//		newNode->parent = parent;
//		newNode->name = node.name;
//		newNode->matrix = Math::matrix4D();
//
//		// Node with children
//		if (node.children.size() > 0) 
//		{
//			for (size_t i = 0; i < node.children.size(); i++) 
//			{
//				LoadNode(newNode, model.nodes[node.children[i]], node.children[i], model, indexBuffer, vertexBuffer, globalscale);
//			}
//		}
//
//		//TODO: load translation matrix
//
//		// Node contains mesh data
//		if (node.mesh > -1) 
//		{
//			const tinygltf::Mesh mesh = model.meshes[node.mesh];
//			Mesh newMesh;
//			newMesh.uniformBlock.matrix = newNode->matrix;
//			pipeline->CreateBuffer(sizeof(newMesh.uniformBlock), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, newMesh.uniformBuffer.buffer, newMesh.uniformBuffer.memory);
//			newMesh.uniformBuffer.descriptor = { newMesh.uniformBuffer.buffer, 0, sizeof(newMesh.uniformBlock) };
//
//			for (size_t i = 0; i < mesh.primitives.size(); i++)
//			{
//				const tinygltf::Primitive& primitive = mesh.primitives[i];
//				uint32_t indexStart = static_cast<uint32_t>(indexBuffer.size());
//				uint32_t vertexStart = static_cast<uint32_t>(vertexBuffer.size());
//				uint32_t indexCount = 0;
//				uint32_t vertexCount = 0;
//				Math::vector3D posMin{};
//				Math::vector3D posMax{};
//				bool hasIndices = primitive.indices > -1;
//
//				// Vertices
//				const float* bufferPos = nullptr;
//				const float* bufferNormals = nullptr;
//				const float* bufferTexCoordSet0 = nullptr;
//				const float* bufferTexCoordSet1 = nullptr;
//
//				int posByteStride;
//				int normByteStride;
//				int uv0ByteStride;
//				int uv1ByteStride;
//
//				const tinygltf::Accessor& posAccessor = model.accessors[primitive.attributes.find("POSITION")->second];
//				const tinygltf::BufferView& posView = model.bufferViews[posAccessor.bufferView];
//				bufferPos = reinterpret_cast<const float*>(&(model.buffers[posView.buffer].data[posAccessor.byteOffset + posView.byteOffset]));
//				posMin = Math::vector3D(posAccessor.minValues[0], posAccessor.minValues[1], posAccessor.minValues[2]);
//				posMax = Math::vector3D(posAccessor.maxValues[0], posAccessor.maxValues[1], posAccessor.maxValues[2]);
//				vertexCount = static_cast<uint32_t>(posAccessor.count);
//				posByteStride = posAccessor.ByteStride(posView) ? (posAccessor.ByteStride(posView) / sizeof(float)) : tinygltf::GetNumComponentsInType(TINYGLTF_TYPE_VEC3);
//
//				if (primitive.attributes.find("NORMAL") != primitive.attributes.end()) 
//				{
//					const tinygltf::Accessor& normAccessor = model.accessors[primitive.attributes.find("NORMAL")->second];
//					const tinygltf::BufferView& normView = model.bufferViews[normAccessor.bufferView];
//					bufferNormals = reinterpret_cast<const float*>(&(model.buffers[normView.buffer].data[normAccessor.byteOffset + normView.byteOffset]));
//					normByteStride = normAccessor.ByteStride(normView) ? (normAccessor.ByteStride(normView) / sizeof(float)) : tinygltf::GetNumComponentsInType(TINYGLTF_TYPE_VEC3);
//				}
//				if (primitive.attributes.find("TEXCOORD_0") != primitive.attributes.end()) 
//				{
//					const tinygltf::Accessor& uvAccessor = model.accessors[primitive.attributes.find("TEXCOORD_0")->second];
//					const tinygltf::BufferView& uvView = model.bufferViews[uvAccessor.bufferView];
//					bufferTexCoordSet0 = reinterpret_cast<const float*>(&(model.buffers[uvView.buffer].data[uvAccessor.byteOffset + uvView.byteOffset]));
//					uv0ByteStride = uvAccessor.ByteStride(uvView) ? (uvAccessor.ByteStride(uvView) / sizeof(float)) : tinygltf::GetNumComponentsInType(TINYGLTF_TYPE_VEC2);
//				}
//				if (primitive.attributes.find("TEXCOORD_1") != primitive.attributes.end()) 
//				{
//					const tinygltf::Accessor& uvAccessor = model.accessors[primitive.attributes.find("TEXCOORD_1")->second];
//					const tinygltf::BufferView& uvView = model.bufferViews[uvAccessor.bufferView];
//					bufferTexCoordSet1 = reinterpret_cast<const float*>(&(model.buffers[uvView.buffer].data[uvAccessor.byteOffset + uvView.byteOffset]));
//					uv1ByteStride = uvAccessor.ByteStride(uvView) ? (uvAccessor.ByteStride(uvView) / sizeof(float)) : tinygltf::GetNumComponentsInType(TINYGLTF_TYPE_VEC2);
//				}
//				for (size_t v = 0; v < posAccessor.count; v++) 
//				{
//					Vertex vert{};
//					vert.pos = Math::vector3D(Math::vector3D(bufferPos[v * posByteStride])) * 0.5f;
//					vert.normal = ((Math::vector3D(bufferNormals ? Math::vector3D(bufferNormals[v * normByteStride]) : Math::vector3D(0.0f)))).normalizeRe();
//					vert.UV = *(bufferTexCoordSet0 ? Math::vector2D(bufferTexCoordSet0[v * uv0ByteStride]) : 0.0f);
//					//vert.UV[1] = *(bufferTexCoordSet1 ? Math::vector2D(bufferTexCoordSet1[v * uv1ByteStride]) : 0.0f);
//
//					vertexBuffer.push_back(vert);
//
//				}
//
//				// Indices
//				if (hasIndices)
//				{
//					const tinygltf::Accessor& accessor = model.accessors[primitive.indices > -1 ? primitive.indices : 0];
//					const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
//					const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];
//
//					indexCount = static_cast<uint32_t>(accessor.count);
//					const void* dataPtr = &(buffer.data[accessor.byteOffset + bufferView.byteOffset]);
//
//					switch (accessor.componentType) 
//					{
//					case TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT: 
//					{
//						const uint32_t* buf = static_cast<const uint32_t*>(dataPtr);
//						for (size_t index = 0; index < accessor.count; index++) 
//						{
//							indexBuffer.push_back(buf[index] + vertexStart);
//						}
//						break;
//					}
//					case TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT: 
//					{
//						const uint16_t* buf = static_cast<const uint16_t*>(dataPtr);
//						for (size_t index = 0; index < accessor.count; index++) 
//						{
//							indexBuffer.push_back(buf[index] + vertexStart);
//						}
//						break;
//					}
//					case TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE: 
//					{
//						const uint8_t* buf = static_cast<const uint8_t*>(dataPtr);
//						for (size_t index = 0; index < accessor.count; index++) 
//						{
//							indexBuffer.push_back(buf[index] + vertexStart);
//						}
//						break;
//					}
//					default:
//						std::cerr << "Index component type " << accessor.componentType << " not supported!" << std::endl;
//						return;
//					}
//				}
//
//				Primitive* newPrimitive = new Primitive(indexStart, indexCount, vertexCount, primitive.material > -1 ? materials[primitive.material] : materials.back());
//				newMesh.primitives.push_back(newPrimitive);
//			}
//			newNode->mesh = newMesh;
//		}
//
//		if (parent) 
//		{
//			parent->children.push_back(newNode);
//		}
//		else 
//		{
//			nodes.push_back(newNode);
//		}
//		linearNodes.push_back(newNode);
//	}
//	void MeshResource::DrawNode(Node* node, VkCommandBuffer commandBuffer)
//	{
//		for (Primitive* primitive : node->mesh.primitives) 
//		{
// 			vkCmdDrawIndexed(commandBuffer, primitive->indexCount, 1, primitive->firstIndex, 0, 0);
//		}
//		for (auto& child : node->children) {
//			DrawNode(child, commandBuffer);
//		}
//	}
//
//	void Render::MeshResource::CreateVertexBuffer(std::vector<Vertex> vertexBuffer)
//	{
//		size_t vertexBufferSize = vertexBuffer.size() * sizeof(Vertex);
//
//		VkBuffer stagingBuffer;
//		VkDeviceMemory stagingBufferMemory;
//		pipeline->CreateBuffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
//
//		void* data;
//		vkMapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, 0, vertexBufferSize, 0, &data);
//		memcpy(data, vertexBuffer.data(), (size_t)vertexBufferSize);
//		vkUnmapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory);
//
//		pipeline->CreateBuffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertices.buffer, vertices.memory);
//
//		pipeline->CopyBuffer(stagingBuffer, vertices.buffer, vertexBufferSize);
//
//		vkDestroyBuffer(pipeline->vkInstance->vDevice, stagingBuffer, nullptr);
//		vkFreeMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, nullptr);
//	}
//
//	void Render::MeshResource::CreateIndexBuffer(std::vector<uint32_t> indexBuffer)
//	{
//		size_t indexBufferSize = indexBuffer.size() * sizeof(uint32_t);
//		indices.count = static_cast<uint32_t>(indexBuffer.size());
//
//		VkBuffer stagingBuffer;
//		VkDeviceMemory stagingBufferMemory;
//		pipeline->CreateBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
//
//		void* data;
//		vkMapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, 0, indexBufferSize, 0, &data);
//		memcpy(data, indexBuffer.data(), (size_t)indexBufferSize);
//		vkUnmapMemory(pipeline->vkInstance->vDevice, stagingBufferMemory);
//
//		pipeline->CreateBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indices.buffer, indices.memory);
//
//		pipeline->CopyBuffer(stagingBuffer, indices.buffer, indexBufferSize);
//
//		vkDestroyBuffer(pipeline->vkInstance->vDevice, stagingBuffer, nullptr);
//		vkFreeMemory(pipeline->vkInstance->vDevice, stagingBufferMemory, nullptr);
//	}
//}
//
