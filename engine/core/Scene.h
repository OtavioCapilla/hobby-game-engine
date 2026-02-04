#pragma once

#include <vector>

#include <engine/core/GameObject.h>
#include <engine/core/Camera2D.h>
#include <engine/world/Tilemap.h>
#include <engine/ecs/World.h>

struct SDL_Renderer;

class Scene
{
public:
    Scene();

    void update(float deltaTime);
    void render(SDL_Renderer *renderer);

    void addObject(const GameObject &object);

    Camera2D &getCamera();

    World &getWorld();

    Tilemap &getTilemap();
    std::vector<GameObject> &getObjects();

private:
    std::vector<GameObject> objects;
    Camera2D camera;
    Tilemap tilemap;
    World world;
};