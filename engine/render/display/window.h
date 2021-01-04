#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GLFW/glfw3.h>

#include <cstdint>
#include <functional>

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

		/// set key press function callback
		void SetKeyPressFunction(const std::function<void(int, int, int, int)>& func);
		/// set mouse press function callback
		void SetMousePressFunction(const std::function<void(int, int, int)>& func);
		/// set mouse move function callback
		void SetMouseMoveFunction(const std::function<void(double, double)>& func);
		/// set mouse enter leave function callback
		void SetMouseEnterLeaveFunction(const std::function<void(bool)>& func);
		/// set mouse scroll function callback
		void SetMouseScrollFunction(const std::function<void(double, double)>& func);
		
		GLFWwindow* window;
		int width, height;

	private:
		uint8_t windowCount{0};
		const char* title;
		//State for when frambuffer is resized
		bool frambufferResize{ false };

		Render::VulkanInstance* instance;
		Render::GraphicsPipeline* pipeline;

		/// static key press callback
		static void StaticKeyPressCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
		/// static mouse press callback
		static void StaticMousePressCallback(GLFWwindow* win, int button, int action, int mods);
		/// static mouse move callback
		static void StaticMouseMoveCallback(GLFWwindow* win, double x, double y);
		/// static mouse enter/leave callback
		static void StaticMouseEnterLeaveCallback(GLFWwindow* win, int mode);
		/// static mouse scroll callback
		static void StaticMouseScrollCallback(GLFWwindow* win, double x, double y);
		/// Static window resize callback
		static void StaticWindowSizeCallback(GLFWwindow* win, int width, int height);

		/// function for key press callbacks
		std::function<void(int, int, int, int)> keyPressCallback;
		/// function for mouse press callbacks
		std::function<void(int, int, int)> mousePressCallback;
		/// function for mouse move callbacks
		std::function<void(double, double)> mouseMoveCallback;
		/// function for mouse enter/leave callbacks
		std::function<void(bool)> mouseLeaveEnterCallback;
		/// function for mouse scroll callbacks
		std::function<void(double, double)> mouseScrollCallback;
	};


	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		Window::SetKeyPressFunction(const std::function<void(int, int, int, int)>& func)
	{
		this->keyPressCallback = func;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		Window::SetMousePressFunction(const std::function<void(int, int, int)>& func)
	{
		this->mousePressCallback = func;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		Window::SetMouseMoveFunction(const std::function<void(double, double)>& func)
	{
		this->mouseMoveCallback = func;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		Window::SetMouseEnterLeaveFunction(const std::function<void(bool)>& func)
	{
		this->mouseLeaveEnterCallback = func;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		Window::SetMouseScrollFunction(const std::function<void(double, double)>& func)
	{
		this->mouseScrollCallback = func;
	}
}

#endif // !_WINDOW_H_
