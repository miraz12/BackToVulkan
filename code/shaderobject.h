#ifndef _SHADER_OBJECT_H_
#define _SHADER_OBJECT_H_

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace Render
{
	class ShaderObject
	{
	public:
		ShaderObject() {};
		ShaderObject(VkDevice vDevice, const std::string& vertex, const std::string& fragment, VkPipelineShaderStageCreateInfo shaderStages[]);
		~ShaderObject();

	private:
		static std::vector<char> readFile(const std::string& filename);
		VkShaderModule createShaderModule(const std::vector<char>& code);

		VkDevice vDevice;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
	};
}

#endif // !_SHADER_OBJECT_H_