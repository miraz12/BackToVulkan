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
		VulkanInstance(){};
		VulkanInstance(Display::Window* win);
		~VulkanInstance() = default;

		void InitVulkan();
		void RecreateSwapChain();
		void Cleanup();
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		

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
		//Vulkan swap chain info
		SwapChainVars swapChain;




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