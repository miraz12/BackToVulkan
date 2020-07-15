#include "graphicspipeline.h"
#include "window.h"

namespace Display
{
	Window::Window() :
		window(nullptr),
		instance(nullptr),
		pipeline(nullptr),
		width(800),
		height(800),
		title("Vulkan window")
	{
		//empty
	}

	bool Window::Open()
	{
		if (windowCount == 0)
			if (!glfwInit()) return false;

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

		instance = new Render::VulkanInstance(this);
		instance->InitVulkan();
		pipeline = new Render::GraphicsPipeline(instance);

		return true;
	}

	void Window::Close()
	{
		pipeline->Cleanup();
		instance->Cleanup();
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::Update()
	{
		glfwPollEvents();
		if (frambufferResize)
		{
			RecreateSwapChain();
			frambufferResize = false;
		}

		pipeline->DrawFrame();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}
	void Window::RecreateSwapChain()
	{
		width = 0;
		height = 0;
		glfwGetFramebufferSize(window, &width, &height);
		while (width == 0 || height == 0) //Minimized, wait for maximization
		{
			glfwGetFramebufferSize(window, &width, &height);
			glfwWaitEvents();
		}
		instance->RecreateSwapChain();
		pipeline->RecreateSwapChain();
	}
	const char** Window::GetRequiredExtensions(uint32_t* count)
	{
		return glfwGetRequiredInstanceExtensions(count);
	}
}

