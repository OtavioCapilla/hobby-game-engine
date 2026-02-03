#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL_scancode.h>

class Input
{
public:
    static void bind(const std::string &action, SDL_Scancode key);

    static bool isActionPressed(const std::string &action);

private:
    static std::unordered_map<std::string, std::vector<SDL_Scancode>> bindings;
};