#include "Scene.h"

#include <engine/systems/MovementSystem.h>
#include <engine/systems/RenderSystem.h>
#include <engine/systems/CollisionSystem.h>

Scene::Scene() : tilemap(32)
{
}

void Scene::addObject(const GameObject &object)
{
    objects.push_back(object);
}

Tilemap &Scene::getTilemap()
{
    return tilemap;
}

void Scene::update(float deltaTime)
{
    if (objects.empty()) return;

    GameObject& player = objects[0];

    MovementSystem::moveX(
        player.transform,
        player.velocity.x,
        deltaTime
    );

    tilemap.resolveCollisionsX(player);

    MovementSystem::moveY(
        player.transform,
        player.velocity.y,
        deltaTime
    );

    tilemap.resolveCollisionsY(player);

    camera.setPosition(player.transform.position);
}

void Scene::render(SDL_Renderer *renderer)
{
    RenderSystem::drawTilemap(renderer, tilemap, camera);
    for (const auto &obj : objects)
    {
        if (obj.sprite)
        {
            RenderSystem::drawSprite(renderer, obj.transform, *obj.sprite, camera);
        }
        RenderSystem::drawCollider(
            renderer,
            obj.transform,
            obj.collider,
            camera);
    }
}

Camera2D &Scene::getCamera()
{
    return camera;
}

std::vector<GameObject> &Scene::getObjects()
{
    return objects;
}