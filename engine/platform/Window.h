#pragma once

struct SDL_Window;

class Window {
    public:
        Window();
        ~Window();

        bool isOpen() const;
        SDL_Window* getSDLWindow() const;

    private:
        SDL_Window* window;
        bool open;
};