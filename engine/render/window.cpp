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

		glfwSetKeyCallback(this->window, Window::StaticKeyPressCallback);
		glfwSetMouseButtonCallback(this->window, Window::StaticMousePressCallback);
		glfwSetCursorPosCallback(this->window, Window::StaticMouseMoveCallback);
		glfwSetCursorEnterCallback(this->window, Window::StaticMouseEnterLeaveCallback);
		glfwSetScrollCallback(this->window, Window::StaticMouseScrollCallback);
		glfwSetWindowSizeCallback(this->window, Window::StaticWindowSizeCallback);

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
	void Window::StaticKeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		if (nullptr != app->keyPressCallback) app->keyPressCallback(key, scancode, action, mods);
	}
	void Window::StaticMousePressCallback(GLFWwindow* window, int button, int action, int mods)
	{
		auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		if (nullptr != app->mousePressCallback) app->mousePressCallback(button, action, mods);
	}
	void Window::StaticMouseMoveCallback(GLFWwindow* window, double x, double y)
	{
		auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		if (nullptr != app->mouseMoveCallback) app->mouseMoveCallback(x, y);
	}
	void Window::StaticMouseEnterLeaveCallback(GLFWwindow* window, int mode)
	{
		auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		if (nullptr != app->mouseLeaveEnterCallback) app->mouseLeaveEnterCallback(mode == 0);
	}
	void Window::StaticMouseScrollCallback(GLFWwindow* window, double x, double y)
	{
		auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		if (nullptr != app->mouseScrollCallback) app->mouseScrollCallback(x, y);
	}
	void Window::StaticWindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		width, height;
		auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		app->frambufferResize = true;
	}
}

