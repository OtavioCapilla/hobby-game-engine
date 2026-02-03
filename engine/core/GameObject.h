#pragma once

#include <engine/core/Transform.h>
#include <engine/math/Vector2.h>
#include <engine/graphics/Sprite.h>
#include <engine/physics/Collider.h>

struct GameObject
{
    Transform transform;
    Vector2 velocity;
    Sprite *sprite;
    Collider collider;
};