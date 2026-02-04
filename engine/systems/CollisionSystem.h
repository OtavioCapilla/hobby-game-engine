#pragma once

#include <engine/ecs/World.h>
#include <engine/world/Tilemap.h>

class CollisionSystem
{
public:
    static bool checkAABB(const Vector2 &posA, const Vector2 &sizeA,
                                const Vector2 &posB, const Vector2 &sizeB);

    static void resolve(World &world, Tilemap &tilemap);
};