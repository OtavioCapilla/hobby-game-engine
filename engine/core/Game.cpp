#include <engine/core/Game.h>
#include <engine/core/Time.h>
#include <engine/systems/InputSystem.h>
#include <engine/graphics/Texture.h>
#include <engine/math/Vector2.h>

#include <SDL2/SDL_scancode.h>
#include <thread>
#include <iostream>
#include <engine/input/Input.h>

Texture *playerTexture = nullptr;

Game::Game(const GameConfig &cfg)
    : config(cfg),
      running(true),
      window(),
      renderer(window),
      assets(renderer.getSDLRenderer())
{
    Input::bind("move_left", SDL_SCANCODE_A);
    Input::bind("move_left", SDL_SCANCODE_LEFT);

    Input::bind("move_right", SDL_SCANCODE_D);
    Input::bind("move_right", SDL_SCANCODE_RIGHT);

    Input::bind("move_up", SDL_SCANCODE_W);
    Input::bind("move_up", SDL_SCANCODE_UP);

    Input::bind("move_down", SDL_SCANCODE_S);
    Input::bind("move_down", SDL_SCANCODE_DOWN);

    Input::bind("quit", SDL_SCANCODE_ESCAPE);

    Texture *tilesTex = assets.getTexture(config.assetRoot + "tileset.png");
    std::cout << "Tileset texture size: "
              << tilesTex->getWidth() << "x"
              << tilesTex->getHeight() << std::endl;
    Tileset *tileset = new Tileset(tilesTex, 32);

    scene.getTilemap().setTileset(tileset);

    scene.getTilemap().loadLayerFromCSV(
        "background", config.assetRoot + "level_bg.csv");

    scene.getTilemap().loadLayerFromCSV(
        "solid", config.assetRoot + "level_solid.csv");

    scene.getTilemap().loadLayerFromCSV(
        "decoration", config.assetRoot + "level_deco.csv");
    Texture *playerTex = assets.getTexture(config.assetRoot + "player.png");

    GameObject player;
    player.velocity = {100.0f, 0.0f};
    player.sprite = new Sprite(playerTex, {64.0f, 64.0f});
    player.collider.size = {64.0f, 64.0f};

    scene.addObject(player);
}

void Game::run()
{
    Time::init();

    while (running && window.isOpen())
    {
        Time::update();

        processInput();
        update();
        render();
    }
}

void Game::processInput()
{
    InputSystem::update();

    if (InputSystem::quitRequested()) {
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

    auto &player = scene.getObjects()[0];
    Vector2 direction = getMovementDirection().normalized();
    float speed = 200.0f;

    player.velocity = direction * speed;
}

void Game::render()
{
    renderer.clear();
    scene.render(renderer.getSDLRenderer());
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
