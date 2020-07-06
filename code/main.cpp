#include <stdexcept>
#include <cstdlib>
#include <iostream>

#include "window.h"

class RenderApplication {
public:
	void Open()
	{
		win = new Display::Window();
		win->Open();
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
		
		win->Close();
	}

private:
	
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