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
	class GraphicsPipeline;

	class GraphicsProperty
	{
	public:
		GraphicsProperty(GraphicsPipeline * vInstance);
		GraphicsProperty() = default;
		~GraphicsProperty();

		MeshResource* mesh{ nullptr };

	private:


		GraphicsPipeline* pipeline;
	};
}

#endif // !_GRAPHICS_COMPONENT_H_
