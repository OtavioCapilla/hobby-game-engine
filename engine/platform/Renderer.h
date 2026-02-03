#pragma once

struct SDL_Renderer;

class Window;

class Renderer {
    public:
        Renderer(Window& window);
        ~Renderer();

        void clear();
        void present();

        SDL_Renderer* getSDLRenderer() const;

    private:
        SDL_Renderer* renderer;
};