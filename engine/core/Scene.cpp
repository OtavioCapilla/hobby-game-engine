#include "Scene.h"

#include <engine/systems/MovementSystem.h>
#include <engine/systems/RenderSystem.h>
#include <engine/systems/CollisionSystem.h>
#include <engine/systems/CameraSystem.h>
#include <engine/systems/InputECSSystem.h>
#include <engine/systems/PlayerControlSystem.h>

Scene::Scene() : tilemap(32)
{
}

World &Scene::getWorld()
{
    return world;
}

const World &Scene::getWorld() const
{
    return world;
}

Tilemap &Scene::getTilemap()
{
    return tilemap;
}

const Tilemap &Scene::getTilemap() const
{
    return tilemap;
}

void Scene::update(float deltaTime)
{
    InputECSSystem::update(world);
    PlayerControlSystem::update(world, 200.f);

    MovementSystem::update(world, deltaTime);
    CollisionSystem::resolve(world, tilemap);
    CameraSystem::update(world, camera);
}

void Scene::render(SDL_Renderer *renderer, AssetManager &assets)
{
    // Tilemaps
    RenderSystem::drawTilemap(renderer, tilemap, camera);

    // Sprites ECS
    for (auto &[entity, sprite] : world.sprites)
    {
        if (!world.transforms.has(entity))
            continue;

        const auto &transform = world.transforms.get(entity);

        RenderSystem::drawSprite(
            renderer,
            assets,
            transform,
            sprite,
            camera);
    }
}

Camera2D &Scene::getCamera()
{
    return camera;
}

const Camera2D &Scene::getCamera() const
{
    return camera;
}

void Scene::clear()
{
    world.clear();
    tilemap.clear();
    camera.reset();
}