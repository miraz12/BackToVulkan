#include "renderapplication.h"


namespace Application
{
	RenderApplication::RenderApplication()
	{
		win = new Display::Window();
		camera = Display::CameraView::GetInstance();
		keyHandler = Input::KeyHandler::GetInstance();
	}

	RenderApplication::~RenderApplication()
	{
		// empty
	}

	bool RenderApplication::Open()
	{
		keyHandler->Init(win);
		
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
			camera->UpdateCamera(win->width, win->height);
		}

		Close();
	}

	void RenderApplication::Close()
	{
		win->Close();
	}
}