#pragma once

#include <engine/core/Scene.h>
#include <engine/graphics/AssetManager.h>
#include <engine/core/GameConfig.h>

class GameSetup
{
public:
    static void setup(Scene &scene, AssetManager &assetManager, const GameConfig &config);
};