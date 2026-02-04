#pragma once

#include <string>
#include <engine/world/Tilemap.h>

class TilemapSerializer
{
public:
    static bool save(const Tilemap &tilemap, const std::string &path);
    static bool load(Tilemap &tilemap, const std::string &path);
};
