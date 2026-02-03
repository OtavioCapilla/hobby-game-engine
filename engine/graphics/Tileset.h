#pragma once

#include <engine/graphics/Texture.h>
#include <engine/math/Vector2.h>
#include <SDL2/SDL_rect.h>

class Tileset
{
public:
    Tileset(Texture *texture, int tileSize);

    SDL_Rect getTileRect(int tileId) const;
    int getTileSize() const;
    Texture *getTexture() const;

private:
    Texture *texture;
    int tileSize;
    int tilesPerRow;
};