#pragma once

#include <SDL2/SDL.h>

class InputSystem {
public:
    static bool quitRequested();

    static bool isKeyDown(int scancode);

    static bool pollEvent(SDL_Event& outEvent);

private:
    static bool s_quit;
};
