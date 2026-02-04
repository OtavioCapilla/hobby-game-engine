#pragma once

#include <engine/ecs/World.h>

class MovementSystem
{
public:
    static void update(World &world, float dt);
};