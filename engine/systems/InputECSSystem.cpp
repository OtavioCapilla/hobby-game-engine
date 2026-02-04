#include "InputECSSystem.h"

#include <engine/input/Input.h>
#include <engine/ecs/components/InputIntent.h>

void InputECSSystem::update(World& world)
{
    for (auto& [entity, intent] : world.inputIntents) {

        Vector2 dir{0.f, 0.f};

        if (Input::isActionPressed("move_left"))  dir.x -= 1.f;
        if (Input::isActionPressed("move_right")) dir.x += 1.f;
        if (Input::isActionPressed("move_up"))    dir.y -= 1.f;
        if (Input::isActionPressed("move_down"))  dir.y += 1.f;

        intent.move = dir;
    }
}
