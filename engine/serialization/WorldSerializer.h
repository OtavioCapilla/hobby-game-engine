#pragma once

#include <string>
#include <engine/ecs/World.h>
#include <engine/vendor/json/json.hpp>

class WorldSerializer {
public:
    static void save(const World &world, nlohmann::json &out);
    static void load(World &world, const nlohmann::json &in);
};