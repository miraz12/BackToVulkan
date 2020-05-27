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
		void Cleanup();

	private:
		//GLFW window
		Display::Window* window;
		//Vulkan instance
		VkInstance instance;
		//Debug messenger callback function
		VkDebugUtilsMessengerEXT debugMessenger;
		//Physical gpu device TODO: Let device be its own class?		
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

		struct QueueFamilyIndices {
			uint32_t graphicsFamily;
		};

		void CreateInstance();
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		void SetupDebugMessenger();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT & createInfo);
		bool IsDeviceSuitable(VkPhysicalDevice device);
		void PickPhysicalDevice();
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		

		
	};
}
