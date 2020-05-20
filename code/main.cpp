#include "window.h"

int main()
{
	
	Display::Window* win = new Display::Window();

	win->Open();

	while (!glfwWindowShouldClose(win->window))
	{
		win->Update();
	}

	win->Close();

	return 0;
}