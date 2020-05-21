#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

#include "window.h"

namespace Render
{
	class VulkanWrapper
	{
	public:
		VulkanWrapper() {};
		VulkanWrapper(Display::Window* win);
		~VulkanWrapper() = default;

		void InitVulkan();
		void SetupDebugMessenger();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT & createInfo);
		void Cleanup();

	private:
		Display::Window* window;
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;

		void CreateInstance();
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();

		
	};
}
