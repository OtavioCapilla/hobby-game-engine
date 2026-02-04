#pragma once

#include <engine/core/Scene.h>
#include <engine/platform/Window.h>
#include <engine/platform/Renderer.h>
#include <engine/graphics/AssetManager.h>
#include <engine/core/GameConfig.h>
#include <engine/ecs/Entity.h>

class Game
{
public:
    explicit Game(const GameConfig &config);

    void run();

    Scene &getScene();
    AssetManager &getAssets();

    void setPlayer(EntityID id);

private:
    EntityID player = INVALID_ENTITY;
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