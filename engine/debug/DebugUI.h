#pragma once

#include <SDL2/SDL.h>
#include <engine/ecs/World.h>

class DebugUI
{
public:
    static void init(SDL_Window *window, SDL_Renderer *renderer);
    static void shutdown();

    static void beginFrame();
    static void draw(World &world);
    static void endFrame();
    static bool isInitialized();
};