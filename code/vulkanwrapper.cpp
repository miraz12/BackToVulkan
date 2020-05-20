#include "vulkanwrapper.h"
#include <stdexcept>

const std::vector<const char*> validationLayers = {
"VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

namespace Render
{
	void VulkanWrapper::InitVulkan()
	{
		CreateInstance();

	
	}

	void VulkanWrapper::Cleanup()
	{
		vkDestroyInstance(instance, nullptr);
	}

	void VulkanWrapper::CreateInstance()
	{
		if (enableValidationLayers && !checkValidationLayerSupport()) 
			throw std::runtime_error("validation layers requested, but not available!");

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		if (enableValidationLayers) 
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) 
		{
			throw std::runtime_error("failed to create instance!");
		}
	}

	bool VulkanWrapper::checkValidationLayerSupport() 
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers) 
		{
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) 
			{
				if (strcmp(layerName, layerProperties.layerName) == 0) 
				{
					layerFound = true;
					break;
				}
			}

			if (!layerFound) 
			{
				return false;
			}
		}
		return true;
	}

	std::vector<const char*> VulkanWrapper::getRequiredExtensions()
	{
		//TODO: Wrapp glfw functions and pass pointer to window to this class.

		//uint32_t glfwExtensionCount = 0;
		//const char** glfwExtensions;
		//glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		//std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		//if (enableValidationLayers) {
		//	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		//}

		//return extensions;
	}

}