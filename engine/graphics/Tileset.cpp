#include "Tileset.h"

#include <iostream>

Tileset::Tileset(Texture *texture, int tileSize)
    : texture(texture), tileSize(tileSize)
{
    if (!texture || texture->getWidth() < tileSize) {
        std::cerr << "Invalid tileset texture size!" << std::endl;
        tilesPerRow = 0;
        return;
    }
    tilesPerRow = texture->getWidth() / tileSize;
}

SDL_Rect Tileset::getTileRect(int tileId) const
{
    if (tilesPerRow == 0) {
        return SDL_Rect{0, 0, 0, 0};
    }

    int index = tileId - 1;

    int x = (index % tilesPerRow) * tileSize;
    int y = (index / tilesPerRow) * tileSize;

    return SDL_Rect{ x, y, tileSize, tileSize};
};

int Tileset::getTileSize() const
{
    return tileSize;
}

Texture* Tileset::getTexture() const
{
    return texture;
}