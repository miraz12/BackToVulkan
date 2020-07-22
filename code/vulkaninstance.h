#ifndef _VULKAN_INSTANCE_H_
#define _VULKAN_INSTANCE_H_

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include <string>

namespace Display
{
	class Window;
}

namespace Render
{
	struct SwapChainVars
	{
		//Vulkan swap chain
		VkSwapchainKHR swapChain;
		//Vulkan swap chain images
		std::vector<VkImage> swapChainImages;
		//Vulkan swap chain image format
		VkFormat swapChainImageFormat;
		//Vulkan swap chain extent
		VkExtent2D swapChainExtent;
		//Vulkan image views
		std::vector<VkImageView> swapChainImageViews;
	};

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		bool isComplete()
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	class VulkanInstance
	{
	public:
		VulkanInstance() = default;
		VulkanInstance(Display::Window* win);
		~VulkanInstance() = default;

		void InitVulkan();
		void RecreateSwapChain();
		void Cleanup();
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
		VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

		//GLFW windowPtr pointer
		Display::Window* windowPtr{ nullptr };
		//Vulkan instance
		VkInstance instance{VK_NULL_HANDLE};
		//Vulkan surface
		VkSurfaceKHR surface{ VK_NULL_HANDLE };
		//Vulkan device
		VkDevice vDevice{ VK_NULL_HANDLE };
		//Vulkan graphics queue
		VkQueue graphicsQueue{ VK_NULL_HANDLE };
		//Vulkan presentation queue
		VkQueue presentQueue{ VK_NULL_HANDLE };
		//Debug messenger callback function
		VkDebugUtilsMessengerEXT debugMessenger{ VK_NULL_HANDLE };
		//Physical gpu device TODO: Let device be its own class?		
		VkPhysicalDevice physicalDevice{ VK_NULL_HANDLE };
		//Vulkan swap chain info
		SwapChainVars swapChain{0};
		//Number of swap chain images
		uint32_t numImages{0};


	private:

		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};

		void CreateInstance();
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		void SetupDebugMessenger();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT & createInfo);
		bool IsDeviceSuitable(VkPhysicalDevice device);
		void PickPhysicalDevice();
		void CreateLogicalDevice();
		void CreateSurface();
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		void CreateSwapChain();
		void CreateImageViews();
		void CleanupSwapChain();

	};
}
#endif // !_VULKAN_INSTANCE_H_
