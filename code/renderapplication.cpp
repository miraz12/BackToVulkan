#include "renderapplication.h"


namespace Application
{
	RenderApplication::RenderApplication()
	{
		// empty
	}

	RenderApplication::~RenderApplication()
	{
		// empty
	}

	bool RenderApplication::Open()
	{
		win = new Display::Window();
		if (win->Open())
		{

			return true;
		}

		return false;
	}

	void RenderApplication::Run()
	{
		while (!glfwWindowShouldClose(win->window))
		{
			win->Update();
		}

		Close();
	}

	void RenderApplication::Close()
	{
		win->Close();
	}
}