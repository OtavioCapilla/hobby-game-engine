#include "GameSetup.h"

#include <engine/graphics/Tileset.h>
#include <engine/core/GameObject.h>
#include <engine/input/Input.h>
#include <engine/ecs/World.h>
#include <engine/ecs/components/CameraTarget.h>
#include <engine/ecs/components/CameraOffset.h>
#include <engine/ecs/components/InputIntent.h>

#include <SDL2/SDL_scancode.h>

EntityID GameSetup::setup(Scene &scene, AssetManager &assets, const GameConfig &config)
{
    World &world = scene.getWorld();

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
    EntityID player = world.createEntity();

    world.transforms.add(player, Transform{{100.f, 100.f}});
    world.velocities.add(player, Velocity{{0.f, 0.f}});
    world.colliders.add(player, Collider{{64.f, 64.f}});

    Texture *playerTex =
        assets.getTexture(config.assetRoot + "player.png");

    Sprite playerSprite;
    playerSprite.texturePath = config.assetRoot + "player.png";
    playerSprite.size = {64.f, 64.f};

    world.sprites.add(player, playerSprite);

    world.add<CameraTarget>(player, CameraTarget{});
    world.add<CameraOffset>(player, CameraOffset{{15.f, 32.f}});
    world.add<InputIntent>(player, InputIntent{});

    // Enemy object
    EntityID enemy = world.createEntity();

    world.transforms.add(enemy, Transform{{100.f, 100.f}});
    world.velocities.add(enemy, Velocity{{0.f, 0.f}});
    world.colliders.add(enemy, Collider{{64.f, 64.f}});

    Texture *enemyTex =
        assets.getTexture(config.assetRoot + "player.png");

    Sprite enemySprite;
    enemySprite.texturePath = config.assetRoot + "player.png";
    enemySprite.size = {64.f, 64.f};

    world.sprites.add(enemy, enemySprite);

    return player;
}