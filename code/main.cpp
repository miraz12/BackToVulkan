#include <stdexcept>
#include <cstdlib>
#include <iostream>

#include "vulkaninstance.h"
#include "graphicspipeline.h"


class RenderApplication {
public:
	void Open()
	{
		win = new Display::Window();
		win->Open();

		instance = new Render::VulkanInstance(win);
		instance->InitVulkan();
		pipeLine = new Render::GraphicsPipeline(instance);
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
	
	Render::VulkanInstance* instance;
	Render::GraphicsPipeline* pipeLine;
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