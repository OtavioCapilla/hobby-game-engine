#include "MovementSystem.h"

void MovementSystem::update(World& world, float dt)
{
    // Itera por entidades que têm Velocity
    for (auto& [entity, vel] : world.velocities) {

        // Só move se tiver Transform
        if (!world.transforms.has(entity))
            continue;

        auto& transform = world.transforms.get(entity);

        transform.position += vel.value * dt;
    }
}