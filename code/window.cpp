#include "window.h"

namespace Display
{
	Window::Window() :
		window(nullptr),
		width(1920),
		height(1080),
		title("Render window")
	{
		//empty
	}

	Window::~Window()
	{
		//empty
	}

	bool Window::Open()
	{
		if (windowCount == 0)
			if (!glfwInit()) return false;

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		return true;
	}

	void Window::Close()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::Update()
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}
}

