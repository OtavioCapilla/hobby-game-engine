#pragma once

#include <engine/core/GameObject.h>

class CollisionSystem
{
public:
    static bool checkAABB(const GameObject &a, const GameObject &b);

    static void resolveX(GameObject &mover,
                         const GameObject &other);

    static void resolveY(GameObject &mover,
                         const GameObject &other);
};