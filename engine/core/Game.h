#pragma once

#include <engine/core/Scene.h>
#include <engine/platform/Window.h>
#include <engine/platform/Renderer.h>
#include <engine/graphics/AssetManager.h>
#include <engine/core/GameConfig.h>

class Game
{
public:
    explicit Game(const GameConfig &config);

    void run();

private:
    void processInput();
    void update();
    void render();

    Vector2 getMovementDirection() const;

    GameConfig config;
    bool running;
    Window window;
    Renderer renderer;
    AssetManager assets;
    Scene scene;
};