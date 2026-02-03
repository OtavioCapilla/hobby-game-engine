#include "Renderer.h"
#include "Window.h"

#include <SDL2/SDL.h>
#include <iostream>

Renderer::Renderer(Window& window)
    : renderer(nullptr){
        renderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if(!renderer){
            std::cerr << "SDL_CreateRenderer failed: "
                  << SDL_GetError() << "\n";
        }
    }

Renderer::~Renderer() {
    if(renderer){
        SDL_DestroyRenderer(renderer);
    }
}

void Renderer::clear(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::present(){
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::getSDLRenderer() const {
    return renderer;
}