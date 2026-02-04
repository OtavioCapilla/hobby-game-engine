#pragma once

#include <vector>

#include <engine/core/GameObject.h>
#include <engine/core/Camera2D.h>
#include <engine/world/Tilemap.h>
#include <engine/ecs/World.h>
#include <engine/graphics/AssetManager.h>

struct SDL_Renderer;

class Scene
{
public:
    Scene();

    void update(float deltaTime);
    void render(SDL_Renderer *renderer, AssetManager &assets);

    // ===== GETTERS (CONST) =====
    const Camera2D &getCamera() const;
    const World &getWorld() const;
    const Tilemap &getTilemap() const;

    // ===== GETTERS (NON-CONST) =====
    Camera2D &getCamera();
    World &getWorld();
    Tilemap &getTilemap();

    // ===== Reset =====
    void clear();

private:
    Camera2D camera;
    Tilemap tilemap;
    World world;
};