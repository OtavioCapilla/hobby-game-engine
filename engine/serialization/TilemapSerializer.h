#pragma once

#include <string>
#include <engine/world/Tilemap.h>
#include <engine/vendor/json/json.hpp>

class TilemapSerializer
{
public:
    static void save(const Tilemap &tilemap,
                     nlohmann::json &out);

    static void load(Tilemap &tilemap,
                     const nlohmann::json &in);
};
