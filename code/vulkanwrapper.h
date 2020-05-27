#include <vulkan/vulkan.h>
#include <vector>
#include <optional>

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
		//GLFW windowPtr pointer
		Display::Window* windowPtr;
		//Vulkan instance
		VkInstance instance;
		//Vulkan surface
		VkSurfaceKHR surface;
		//Vulkan device
		VkDevice vDevice;
		//Vulkan graphics queue
		VkQueue graphicsQueue;
		//Vulkan presentation queue
		VkQueue presentQueue;
		//Debug messenger callback function
		VkDebugUtilsMessengerEXT debugMessenger;
		//Physical gpu device TODO: Let device be its own class?		
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;
			bool isComplete()
			{
				return graphicsFamily.has_value() && presentFamily.has_value();
			}
		};

		void CreateInstance();
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		void SetupDebugMessenger();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT & createInfo);
		bool IsDeviceSuitable(VkPhysicalDevice device);
		void PickPhysicalDevice();
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		void CreateLogicalDevice();
		void CreateSurface();
		
		
	};
}
