#include "GameSetup.h"

#include <engine/graphics/Tileset.h>
#include <engine/core/GameObject.h>
#include <engine/input/Input.h>

#include <SDL2/SDL_scancode.h>

void GameSetup::setup(Scene &scene, AssetManager &assets, const GameConfig &config)
{
    // Input bindings
    Input::bind("move_left", SDL_SCANCODE_A);
    Input::bind("move_left", SDL_SCANCODE_LEFT);

    Input::bind("move_right", SDL_SCANCODE_D);
    Input::bind("move_right", SDL_SCANCODE_RIGHT);

    Input::bind("move_up", SDL_SCANCODE_W);
    Input::bind("move_up", SDL_SCANCODE_UP);

    Input::bind("move_down", SDL_SCANCODE_S);
    Input::bind("move_down", SDL_SCANCODE_DOWN);

    Input::bind("quit", SDL_SCANCODE_ESCAPE);

    // Tilemap + Tileset
    Texture *tilesTex =
        assets.getTexture(config.assetRoot + "tileset.png");

    Tileset *tileset = new Tileset(tilesTex, 32);

    scene.getTilemap().setTileset(tileset);

    scene.getTilemap().loadLayerFromCSV(
        "background", config.assetRoot + "level_bg.csv");

    scene.getTilemap().loadLayerFromCSV(
        "solid", config.assetRoot + "level_solid.csv");

    scene.getTilemap().loadLayerFromCSV(
        "decoration", config.assetRoot + "level_deco.csv");

    // Player object
    Texture *playerTex =
        assets.getTexture(config.assetRoot + "player.png");

    GameObject player;
    player.transform.position = {64.f, 64.f};
    player.collider.size = {64.f, 64.f};
    player.sprite = new Sprite(playerTex, {64.f, 64.f});

    scene.addObject(player);
}