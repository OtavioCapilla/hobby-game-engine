#pragma once

struct SDL_Renderer;

#include <engine/core/Transform.h>
#include <engine/core/Camera2D.h>
#include <engine/graphics/Sprite.h>
#include <engine/physics/Collider.h>
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