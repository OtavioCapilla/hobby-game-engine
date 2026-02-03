#include "Input.h"
#include <engine/systems/InputSystem.h>

std::unordered_map<std::string, std::vector<SDL_Scancode>> Input::bindings;

void Input::bind(const std::string &action, SDL_Scancode key)
{
    bindings[action].push_back(key);
}

bool Input::isActionPressed(const std::string &action)
{
    if(!bindings.count(action)){
        return false;
    }

    for(SDL_Scancode key: bindings[action]){
        if(InputSystem::isKeyDown(key)){
            return true;
        }
    }
    return false;
}