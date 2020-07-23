#ifndef _RENDER_APPLICATION_H_
#define _RENDER_APPLICATION_H_

#include "core/app.h"
#include "render/window.h"

namespace Application
{
	class RenderApplication : public Core::App {
	public:

		/// constructor
		RenderApplication();
		/// destructor
		~RenderApplication();
		/// open app
		bool Open() override;
		/// run app
		void Run() override;
		/// close app
		void Close() override;

	private:

		Display::Window* win{ nullptr };
	};

}

#endif // !_RENDER_APPLICATION_H_