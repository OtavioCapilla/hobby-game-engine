#pragma once

#include <string>

struct SDL_Texture;
struct SDL_Renderer;

class Texture {
public:
    Texture(SDL_Renderer* renderer, const std::string& path);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    int getWidth() const;
    int getHeight() const;

    SDL_Texture* get() const;

private:
    SDL_Texture* texture;
    int width;
    int height;
};