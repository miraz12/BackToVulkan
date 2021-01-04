#ifndef _GRAPHICS_COMPONENT_H_
#define _GRAPHICS_COMPONENT_H_
#include <vector>
#include <array>
#include <vulkan/vulkan.h>

#include "render/resources/meshresource.h"
#include "core/math/vector3D.h"
#include "core/math/vector2D.h"

namespace Render
{
	class RenderServer;

	class GraphicsProperty
	{
	public:
		GraphicsProperty(RenderServer * vInstance);
		GraphicsProperty() = default;
		~GraphicsProperty();

		MeshResource* mesh{ nullptr };

	private:


		RenderServer* pipeline;
	};
}

#endif // !_GRAPHICS_COMPONENT_H_
