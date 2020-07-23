#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GLFW/glfw3.h>

#include <cstdint>

namespace Render
{
	class VulkanInstance;
	class GraphicsPipeline;
}

namespace Display
{
	class Window
	{
	public:
		/// constructor
		Window();
		/// destructor
		~Window() = default;
		/// open window
		bool Open();
		/// close window
		void Close();
		/// update a tick
		void Update();
		/// swap buffers at end of frame
		void SwapBuffers();
		/// recreates the swap chain if it is invalid
		void RecreateSwapChain();

		///Get required extensions TODO: keep this or pass directly to vulkan wrapper?
		 const char** GetRequiredExtensions(uint32_t* count);
		
		GLFWwindow* window;
		int width, height;

	private:
		uint8_t windowCount{0};
		const char* title;
		//State for when frambuffer is resized
		bool frambufferResize{ false };

		Render::VulkanInstance* instance;
		Render::GraphicsPipeline* pipeline;

		static void framebufferResizeCallback(GLFWwindow* window, int width, int height)
		{
			width, height;
			auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
			app->frambufferResize = true;
		}
	};
}

#endif // !_WINDOW_H_
