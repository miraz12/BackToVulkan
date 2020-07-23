#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include "renderapplication.h"

int main()
{
	try 
	{
		Application::RenderApplication app = Application::RenderApplication();
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