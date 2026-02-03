#include "Texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Texture::Texture(SDL_Renderer *renderer, const std::string &path) : texture(nullptr), width(0), height(0)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface)
    {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    }
    else
    {
        width = surface->w;
        height = surface->h;
    }
    SDL_FreeSurface(surface);
}

Texture::~Texture()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

int Texture::getWidth() const
{
    return width;
}

int Texture::getHeight() const
{
    return height;
}

SDL_Texture* Texture::get() const {
    return texture;
}