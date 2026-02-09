#include "Window.h"

#include <SDL2/SDL.h>
#include <iostream>

Window::Window()
    : window(nullptr), open(true) {
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0){
            std::cerr << "SDL_Init failed: "
                  << SDL_GetError() << "\n";
            open = false;
            return;
        }

        window = SDL_CreateWindow("Fox Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

        if(!window){
            std::cerr << "SDL_CreateWindow failed: "
                  << SDL_GetError() << "\n";
            open = false;
            return;
        }

        std::cout << "Window created successfully\n";
    }

Window::~Window() {
    if(window){
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

bool Window::isOpen() const {
    return open;
}

SDL_Window* Window::getSDLWindow() const {
    return window;
}