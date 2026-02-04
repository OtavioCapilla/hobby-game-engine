#pragma once

#include <engine/ecs/World.h>

class PlayerControlSystem
{
public:
    static void update(World &world, float speed);
};