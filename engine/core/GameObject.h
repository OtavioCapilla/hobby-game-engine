#pragma once

#include <engine/ecs/components/Transform.h>
#include <engine/math/Vector2.h>
#include <engine/ecs/components/Sprite.h>
#include <engine/ecs/components/Collider.h>

struct GameObject
{
    Transform transform;
    Vector2 velocity;
    Sprite *sprite;
    Collider collider;
};