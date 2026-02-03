#include "AssetManager.h"
#include "Texture.h"

#include <iostream>

AssetManager::AssetManager(SDL_Renderer *renderer)
    : renderer(renderer)
{
}

Texture *AssetManager::getTexture(const std::string &path)
{
    auto it = textures.find(path);

    if (it != textures.end())
    {
        return it->second.get();
    }

    auto texture = std::make_unique<Texture>(renderer, path);
    if (!texture->get())
    {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return nullptr;
    }

    Texture *rawPtr = texture.get();
    textures[path] = std::move(texture);
    return rawPtr;
}

void AssetManager::clear()
{
    textures.clear();
}