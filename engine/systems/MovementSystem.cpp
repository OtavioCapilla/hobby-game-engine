#include "MovementSystem.h"

void MovementSystem::update(World& world, float dt)
{
    for (auto& [entity, vel] : world.velocities) {

        if (!world.transforms.has(entity))
            continue;

        auto& transform = world.transforms.get(entity);

        transform.position += vel.value * dt;
    }
}