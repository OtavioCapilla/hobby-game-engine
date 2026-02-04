#include "CameraSystem.h"
#include <engine/ecs/components/CameraTarget.h>
#include <engine/ecs/components/CameraOffset.h>

void CameraSystem::update(World &world, Camera2D &camera)
{
    const Vector2 halfViewport{400.f, 300.f};

    for (auto& [entity, transform] : world.transforms) {

        if (!world.has<CameraTarget>(entity))
            continue;

        Vector2 camPos = transform.position - halfViewport;
        camera.setPosition(camPos);
        break;
    }
}
