#include "graphicscomponent.h"
#include "render/servers/graphicspipeline.h"

namespace Render
{
    GraphicsComponent::GraphicsComponent(GraphicsPipeline * vInstance) : pipeline(vInstance)
    {
        mesh = new MeshResource();
        mesh->LoadModel("resources/models/GLTF/viking_room/scene.gltf", vInstance);
    }

    GraphicsComponent::~GraphicsComponent()
    {
        delete(mesh);
    }
}
