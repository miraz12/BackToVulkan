#ifndef _SHADER_OBJECT_H_
#define _SHADER_OBJECT_H_

#include <string>
#include <vector>

#include "core/renderinterface/vulkaninstance.h"

namespace Render
{
	class ShaderObject
	{
	public:
		ShaderObject() = default;
		ShaderObject(VkDevice vDevice, const std::string& vertex, const std::string& fragment, VkPipelineShaderStageCreateInfo shaderStages[]);
		~ShaderObject();

	private:
		static std::vector<char> readFile(const std::string& filename);
		VkShaderModule createShaderModule(const std::vector<char>& code);

		VkDevice vDevice{ nullptr };
		VkShaderModule vertShaderModule{ VK_NULL_HANDLE };
		VkShaderModule fragShaderModule{ VK_NULL_HANDLE };
	};
}

#endif // !_SHADER_OBJECT_H_