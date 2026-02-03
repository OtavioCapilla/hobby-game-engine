#pragma once

#include <string>
#include <unordered_map>
#include <memory>

struct SDL_Renderer;
class Texture;

class AssetManager
{
public:
    explicit AssetManager(SDL_Renderer *renderer);
    ~AssetManager() = default;

    Texture *getTexture(const std::string &path);

    void clear();

private:
    SDL_Renderer *renderer;

    std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
};