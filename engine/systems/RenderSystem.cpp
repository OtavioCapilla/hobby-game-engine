#include "RenderSystem.h"

#include <SDL2/SDL.h>
#include <engine/ecs/components/Collider.h>
#include <engine/core/GameObject.h>

static inline SDL_Rect toScreenRect(const Vector2 &worldPos,
                                    const Vector2 &size,
                                    const Camera2D &camera)
{
    Vector2 screenPos = worldPos - camera.getPosition();

    SDL_Rect rect;
    rect.x = static_cast<int>(screenPos.x);
    rect.y = static_cast<int>(screenPos.y);
    rect.w = static_cast<int>(size.x);
    rect.h = static_cast<int>(size.y);

    return rect;
}

void RenderSystem::drawRect(SDL_Renderer *renderer,
                            const Transform &transform,
                            const Collider &collider,
                            const Camera2D &camera)
{
    SDL_Rect rect = toScreenRect(
        transform.position,
        collider.size,
        camera);

    SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void RenderSystem::drawSprite(SDL_Renderer *renderer,
                              const Transform &transform,
                              const Sprite &sprite,
                              const Camera2D &camera)
{
    if (!sprite.texture || !sprite.texture->get())
    {
        return;
    }

    SDL_Rect dst = toScreenRect(
        transform.position,
        sprite.size,
        camera);

    SDL_RenderCopy(
        renderer,
        sprite.texture->get(),
        nullptr,
        &dst);
}

void RenderSystem::drawCollider(SDL_Renderer *renderer,
                                const Transform &transform,
                                const Collider &collider,
                                const Camera2D &camera)
{
    SDL_Rect rect = toScreenRect(
        transform.position,
        collider.size,
        camera);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
}

void RenderSystem::drawTilemap(SDL_Renderer *renderer,
                               const Tilemap &tilemap,
                               const Camera2D &camera)
{
    const Tileset *tileset = tilemap.getTileset();
    if (!tileset)
        return;

    int ts = tilemap.getTileSize();

    for (const auto &layer : tilemap.getLayerOrder())
    {
        for (int y = 0; y < tilemap.getHeight(); ++y)
            for (int x = 0; x < tilemap.getWidth(); ++x)
            {

                int id = tilemap.getTile(layer, x, y);
                if (id == 0)
                    continue;

                SDL_Rect src = tileset->getTileRect(id);
                Vector2 pos = tilemap.tileToWorld(x, y) - camera.getPosition();

                SDL_Rect dst{
                    (int)pos.x, (int)pos.y, ts, ts};

                SDL_RenderCopy(renderer,
                               tileset->getTexture()->get(),
                               &src, &dst);
            }
    }
}