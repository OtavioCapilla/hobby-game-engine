#include "PlayerControlSystem.h"

void PlayerControlSystem::update(World &world, float speed)
{
    for (auto &[entity, intent] : world.inputIntents)
    {

        if (!world.has<Velocity>(entity))
            continue;

        Vector2 dir = intent.move;
        if (dir.length() > 0.f)
            dir = dir.normalized();

        world.get<Velocity>(entity).value = dir * speed;
    }
}
