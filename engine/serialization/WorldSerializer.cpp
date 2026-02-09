#include "WorldSerializer.h"

#include <fstream>
#include <set>

using json = nlohmann::json;

static std::set<EntityID> collectEntities(const World &world)
{
    std::set<EntityID> entities;

    for (auto &[id, _] : world.transforms)
        entities.insert(id);
    for (auto &[id, _] : world.velocities)
        entities.insert(id);
    for (auto &[id, _] : world.colliders)
        entities.insert(id);
    for (auto &[id, _] : world.sprites)
        entities.insert(id);
    for (auto &[id, _] : world.inputIntents)
        entities.insert(id);
    for (auto &[id, _] : world.cameraTargets)
        entities.insert(id);
    for (auto &[id, _] : world.cameraOffsets)
        entities.insert(id);

    return entities;
}

void WorldSerializer::save(const World &world, json &out)
{
    json entities;

    for (EntityID entity : collectEntities(world))
    {
        json e;
        e["id"] = entity;

        if (world.has<Transform>(entity))
        {
            const auto &t = world.get<Transform>(entity);
            e["transform"] = {
                {"x", t.position.x},
                {"y", t.position.y}};
        }

        if (world.has<Velocity>(entity))
        {
            const auto &v = world.get<Velocity>(entity);
            e["velocity"] = {
                {"x", v.value.x},
                {"y", v.value.y}};
        }

        if (world.has<Sprite>(entity))
        {
            const auto &s = world.get<Sprite>(entity);
            e["sprite"] = {
                {"texture", s.texturePath},
                {"w", s.size.x},
                {"h", s.size.y}};
        }

        if (world.has<Collider>(entity))
        {
            const auto &c = world.get<Collider>(entity);
            e["collider"] = {
                {"w", c.size.x},
                {"h", c.size.y}};
        }

        entities.push_back(e);
    }

    out["entities"] = entities;
}

void WorldSerializer::load(World &world, const json &in)
{
    world.clear();

    for (const auto &e : in["entities"])
    {
        EntityID id = world.createEntity();

        if (e.contains("transform"))
        {
            world.add<Transform>(id, {{e["transform"]["x"], e["transform"]["y"]}});
        }

        if (e.contains("velocity"))
        {
            world.add<Velocity>(id, {{e["velocity"]["x"], e["velocity"]["y"]}});
        }

        if (e.contains("sprite"))
        {
            world.add<Sprite>(id, {e["sprite"]["texture"],
                                   {e["sprite"]["w"], e["sprite"]["h"]}});
        }

        if (e.contains("collider"))
        {
            world.add<Collider>(id, {{e["collider"]["w"], e["collider"]["h"]}});
        }
    }
}
