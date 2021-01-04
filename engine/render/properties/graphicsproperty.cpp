#include "graphicsproperty.h"
#include "render/servers/graphicspipeline.h"

namespace Render
{
    GraphicsProperty::GraphicsProperty(GraphicsPipeline * vInstance) : pipeline(vInstance)
    {
        mesh = new MeshResource();
        mesh->LoadModel("resources/models/GLTF/viking_room/scene.gltf", vInstance);
    }

    GraphicsProperty::~GraphicsProperty()
    {
        delete(mesh);
    }
}
