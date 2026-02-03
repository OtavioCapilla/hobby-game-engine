#pragma once

#include <engine/core/Transform.h>
#include <engine/math/Vector2.h>

class MovementSystem
{
public:
    static void moveX(Transform &transform, float velocityX, float deltaTime);
    static void moveY(Transform &transform, float velocityY, float deltaTime);
};