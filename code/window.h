#include <GLFW/glfw3.h>
#include <cstdint>

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

		///Get required extensions TODO: keep this or pass directly to vulkan wrapper?
		 const char** GetRequiredExtensions(uint32_t* count);
		
		GLFWwindow* window;

	private:
		uint8_t windowCount{0};
		uint32_t width, height;
		const char* title;

	};
}