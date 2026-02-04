#include <engine/core/Game.h>
#include <engine/core/Time.h>
#include <engine/systems/InputSystem.h>
#include <engine/graphics/Texture.h>
#include <engine/math/Vector2.h>

#include <SDL2/SDL_scancode.h>
#include <thread>
#include <iostream>
#include <engine/input/Input.h>

#include <engine/debug/DebugUI.h>

Texture *playerTexture = nullptr;

Game::Game(const GameConfig &cfg)
    : config(cfg),
      running(true),
      window(),
      renderer(window),
      assets(renderer.getSDLRenderer()),
      scene()
{
    DebugUI::init(window.getSDLWindow(), renderer.getSDLRenderer());
}

void Game::run()
{
    Time::init();

    while (running && window.isOpen())
    {
        Time::update();
        DebugUI::beginFrame();

        processInput();
        update();
        render();
    }

    DebugUI::shutdown();
}

void Game::processInput()
{
    InputSystem::update();

    if (InputSystem::quitRequested())
    {
        running = false;
        return;
    }

    if (Input::isActionPressed("quit"))
    {
        running = false;
    }
}

void Game::update()
{
    scene.update(Time::deltaTime());
}

void Game::render()
{
    renderer.clear();
    scene.render(renderer.getSDLRenderer());

    DebugUI::draw(scene.getWorld());
    DebugUI::endFrame();
    renderer.present();
}

Vector2 Game::getMovementDirection() const
{
    Vector2 dir{0.0f, 0.0f};

    if (Input::isActionPressed("move_left"))
        dir.x -= 1.0f;

    if (Input::isActionPressed("move_right"))
        dir.x += 1.0f;

    if (Input::isActionPressed("move_up"))
        dir.y -= 1.0f;

    if (Input::isActionPressed("move_down"))
        dir.y += 1.0f;

    return dir;
}

Scene &Game::getScene()
{
    return scene;
}

AssetManager &Game::getAssets()
{
    return assets;
}

void Game::setPlayer(EntityID id)
{
    player = id;
}