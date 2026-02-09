#include "InputSystem.h"

bool InputSystem::s_quit = false;

bool InputSystem::pollEvent(SDL_Event& event)
{
    if (!SDL_PollEvent(&event))
        return false;

    if (event.type == SDL_QUIT)
        s_quit = true;

    if (event.type == SDL_KEYDOWN &&
        event.key.keysym.sym == SDLK_ESCAPE)
        s_quit = true;

    return true;
}

bool InputSystem::quitRequested()
{
    return s_quit;
}

bool InputSystem::isKeyDown(int scancode)
{
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    return state[scancode];
}
