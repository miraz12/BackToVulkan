#include "graphicsproperty.h"
#include "render/servers/renderserver.h"

namespace Render
{
    GraphicsProperty::GraphicsProperty(RenderServer * vInstance) : pipeline(vInstance)
    {
        mesh = new MeshResource();
        mesh->LoadModel("resources/models/GLTF/viking_room/scene.gltf", vInstance);
    }

    GraphicsProperty::~GraphicsProperty()
    {
        delete(mesh);
    }
}
