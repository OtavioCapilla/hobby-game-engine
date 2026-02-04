#pragma once

#include <string>
#include <engine/core/Scene.h>

class SceneSerializer
{
public:
    static bool save(const Scene &scene, const std::string &path);
    static bool load(Scene &scene, const std::string &path);
};