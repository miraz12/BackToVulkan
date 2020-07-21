#include "graphicscomponent.h"
#include "graphicspipeline.h"

namespace Render
{
    GraphicsComponent::GraphicsComponent(GraphicsPipeline * vInstance) : pipeline(vInstance)
    {
        mesh = new MeshResource();
        mesh->LoadModel("resources/models/GLTF/viking_room/viking_room.gltf", vInstance);
        //texture = new TextureResource(pipeline, "resources/models/Obj/viking_room/viking_room.png");
    }

    GraphicsComponent::~GraphicsComponent()
    {
        delete(mesh);
        //delete(texture);
    }
}
