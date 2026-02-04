#pragma once

#include <engine/core/Scene.h>
#include <engine/graphics/AssetManager.h>
#include <engine/core/GameConfig.h>
#include <engine/ecs/Entity.h>

class GameSetup
{
public:
    static EntityID setup(Scene &scene, AssetManager &assetManager, const GameConfig &config);
};