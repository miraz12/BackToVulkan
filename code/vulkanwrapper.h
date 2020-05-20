#include <vulkan/vulkan.h>
#include <vector>

namespace Render
{
	class VulkanWrapper
	{
	public:
		VulkanWrapper() {};
		VulkanWrapper(uint32_t extensionCount, const char** extensions) : 
			glfwExtensionCount(extensionCount), glfwExtensions(extensions) {};
		~VulkanWrapper() {};

		void InitVulkan();
		void Cleanup();

	private:
		VkInstance instance;
		uint32_t glfwExtensionCount{0};
		const char** glfwExtensions;

		void CreateInstance();
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
	};
}
