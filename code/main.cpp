#include <stdexcept>
#include <cstdlib>
#include <iostream>

#include "window.h"
#include "vulkanwrapper.h"


class RenderApplication {
public:
	void Open()
	{
		win = new Display::Window();
		win->Open();

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);


		instance = new Render::VulkanWrapper(glfwExtensionCount, glfwExtensions);
		instance->InitVulkan();
	}

	void Run()
	{
		while (!glfwWindowShouldClose(win->window))
		{
			win->Update();
		}

		Close();
	}

	void Close()
	{
		instance->Cleanup();
		win->Close();
	}

private:
	
	Render::VulkanWrapper* instance;
	Display::Window* win;

};

int main()
{

	try 
	{
		RenderApplication app = RenderApplication();
		app.Open();
		app.Run();
	}
	catch (const std::exception& e) 
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return 0;
}