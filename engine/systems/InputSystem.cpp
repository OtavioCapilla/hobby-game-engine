#include "InputSystem.h"

#include <SDL2/SDL.h>
#include <engine/vendor/imgui/backends/imgui_impl_sdl2.h>

bool InputSystem::s_quit = false;

void InputSystem::update(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) {
            s_quit = true;
        }

        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.sym == SDLK_ESCAPE) {
                s_quit = true;
            }
        }
    }
}

bool InputSystem::quitRequested(){
    return s_quit;
}

bool InputSystem::isKeyDown(int scancode) {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    return state[scancode];
}