#pragma once

struct SDL_Renderer;

#include <engine/ecs/components/Transform.h>
#include <engine/core/Camera2D.h>
#include <engine/ecs/components/Sprite.h>
#include <engine/ecs/components/Collider.h>
#include <engine/world/Tilemap.h>

class RenderSystem
{
public:
    static void drawRect(SDL_Renderer *renderer,
                         const Transform &transform,
                         const Collider &collider,
                         const Camera2D &camera);

    static void drawSprite(SDL_Renderer *renderer,
                           const Transform &transform,
                           const Sprite &sprite,
                           const Camera2D &camera);

    static void drawCollider(SDL_Renderer *renderer,
                             const Transform &transform,
                             const Collider &collider,
                             const Camera2D &camera);

    static void drawTilemap(SDL_Renderer *renderer,
                            const Tilemap &tilemap,
                            const Camera2D &camera);
};