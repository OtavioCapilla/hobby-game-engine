#include "ECSInspector.h"

#include <imgui.h>
#include <set>
#include <string>

static std::set<EntityID> collectEntities(const World &world)
{
    std::set<EntityID> entities;

    for (const auto &[id, _] : world.transforms)
        entities.insert(id);

    for (const auto &[id, _] : world.velocities)
        entities.insert(id);

    for (const auto &[id, _] : world.sprites)
        entities.insert(id);

    for (const auto &[id, _] : world.colliders)
        entities.insert(id);

    for (const auto &[id, _] : world.inputIntents)
        entities.insert(id);

    for (const auto &[id, _] : world.cameraTargets)
        entities.insert(id);

    for (const auto &[id, _] : world.cameraOffsets)
        entities.insert(id);

    return entities;
}

void ECSInspector::draw(World &world)
{
    ImGui::Begin("ECS Inspector");

    auto entities = collectEntities(world);

    for (EntityID id : entities)
    {

        std::string label = "Entity " + std::to_string(id);

        if (!ImGui::TreeNode(label.c_str()))
            continue;

        if (world.has<Transform>(id))
        {
            const auto &t = world.get<Transform>(id);
            ImGui::Text("Transform");
            ImGui::Text("  Position: (%.2f, %.2f)", t.position.x, t.position.y);
        }

        if (world.has<Velocity>(id))
        {
            const auto &v = world.get<Velocity>(id);
            ImGui::Text("Velocity");
            ImGui::Text("  Value: (%.2f, %.2f)", v.value.x, v.value.y);
        }

        if (world.has<Collider>(id))
        {
            const auto &c = world.get<Collider>(id);
            ImGui::Text("Collider");
            ImGui::Text("  Size: (%.2f, %.2f)", c.size.x, c.size.y);
        }

        if (world.has<Sprite>(id))
        {
            const auto &s = world.get<Sprite>(id);
            ImGui::Text("Sprite");
            ImGui::Text("  Texture: %s", s.texturePath.c_str());
            ImGui::Text("  Size: (%.2f, %.2f)", s.size.x, s.size.y);
        }

        if (world.has<InputIntent>(id))
        {
            const auto &i = world.get<InputIntent>(id);
            ImGui::Text("InputIntent");
            ImGui::Text("  Move: (%.2f, %.2f)", i.move.x, i.move.y);
        }

        if (world.has<CameraTarget>(id))
        {
            ImGui::Text("CameraTarget");
        }

        if (world.has<CameraOffset>(id))
        {
            const auto &o = world.get<CameraOffset>(id);
            ImGui::Text("CameraOffset");
            ImGui::Text("  Offset: (%.2f, %.2f)", o.offset.x, o.offset.y);
        }

        ImGui::TreePop();
    }

    ImGui::End();
}
