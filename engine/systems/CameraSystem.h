#pragma once

#include <engine/ecs/World.h>
#include <engine/core/Camera2D.h>

class CameraSystem
{
public:
    static void update(World &world, Camera2D &camera);
};