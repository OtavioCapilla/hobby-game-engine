# HobbyEngine — A Lightweight 2D C++ Game Engine

HobbyEngine is a modular 2D game engine built in modern C++ (C++20) on top of SDL2 and SDL2_image. It focuses on clarity and simplicity: a minimal API for windowing and rendering, a small set of systems (input, movement, collision, rendering), a tilemap with CSV-based layers, and a straightforward game loop you can extend.

---

## Highlights

- Minimal, readable codebase organized by domain (core, graphics, platform, systems, world)
- SDL2-backed window and renderer with double buffering
- Sprites and basic texture management with caching
- Tilemap rendering from CSV layers with a tileset atlas
- Simple `GameObject` data model with `Transform`, `Sprite`, `Collider`, `Vector2`
- Action-based input mapping (`Input::bind`, `Input::isActionPressed`)
- Basic movement and AABB collision helpers
- Time management (`Time::deltaTime()`) for framerate-independent updates

---

## Architecture Overview

- **Core**: Game loop, scene graph, camera, timing, game objects, config
  - `Game` orchestrates input → update → render
  - `Scene` holds `GameObject` list, `Camera2D`, and `Tilemap`
  - `Time` provides `deltaTime()` updated each frame
  - `GameConfig` supplies runtime configuration such as asset root
- **Platform**: SDL-backed `Window` and `Renderer`
  - `Window` handles SDL window lifecycle
  - `Renderer` wraps an `SDL_Renderer` and provides `clear()`/`present()`
- **Graphics**: Textures, sprites, asset management, tileset
  - `Texture` loads images via SDL2_image and exposes width/height
  - `Sprite` is a lightweight container of `Texture*` + desired size
  - `AssetManager` caches textures by path
  - `Tileset` maps a tile ID to a rect inside a texture atlas
- **Input**: Action binding and query
  - `Input` lets you bind named actions to SDL scancodes and query them
  - `InputSystem` updates the input state and detects quit
- **Systems**: Rendering, movement, collision
  - `RenderSystem` draws sprites, rectangles, colliders, and tilemaps
  - `MovementSystem` moves objects along X/Y
  - `CollisionSystem` checks and resolves AABB collisions
- **World**: Tilemap
  - `Tilemap` loads layer data from CSV files, renders using a `Tileset`, and resolves tile collisions

---

## Project Layout

```
engine/
  core/        Game loop, scene, camera, time, objects, config
  graphics/    Textures, sprites, asset manager, tileset
  input/       Action binding and input system
  math/        Vector2
  physics/     Collider structure
  platform/    SDL window and renderer wrappers
  systems/     Render, movement, collision systems
  world/       Tilemap loading & collisions

games/
  demo/        Example game (executable) and assets
```

Key CMake setup:

- The engine builds as a library target named `engine` (see `engine/CMakeLists.txt`).
- The demo builds as an executable target named `demo` and links against `engine`.
- Public include root is the repository root, so includes use prefixes like `#include <engine/...>`.

---

## Dependencies

- **C++**: C++20-compatible compiler (GCC, Clang)
- **Build**: CMake ≥ 3.20
- **Runtime**: SDL2 and SDL2_image

Install on common Linux distros:

- Debian/Ubuntu:
  ```bash
  sudo apt update
  sudo apt install -y build-essential cmake libsdl2-dev libsdl2-image-dev
  ```
- Arch Linux:
  ```bash
  sudo pacman -S --needed base-devel cmake sdl2 sdl2_image
  ```
- Fedora:
  ```bash
  sudo dnf install -y gcc-c++ cmake SDL2-devel SDL2_image-devel
  ```

---

## Build & Run (Linux)

1. Configure and build:
   ```bash
   mkdir -p build
   cd build
   cmake ..
   make -j
   ```

2. Run the demo (ensure the working directory is the repo root so assets resolve correctly):
   ```bash
   cd /path/to/my_engine    # repository root
   ./build/games/demo/demo
   ```

The demo expects assets under `games/demo/assets/` relative to the current working directory. Running from the repository root ensures paths like `games/demo/assets/player.png` resolve.

---

## Quick Start

Create a minimal game that loads assets and runs the main loop.

- **main.cpp**
  ```cpp
  #include <engine/core/Game.h>
  #include <filesystem>

  int main(){
      GameConfig config;

      auto root = std::filesystem::current_path();
      config.assetRoot = (root / "games/demo/assets/").string();

      Game game(config);
      game.run();
      return 0;
  }
  ```

- **CMakeLists.txt** (top-level)
  ```cmake
  cmake_minimum_required(VERSION 3.20)
  project(HobbyEngine)

  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  add_subdirectory(engine)
  add_subdirectory(games/demo)
  ```

- **CMakeLists.txt** (your game target)
  ```cmake
  add_executable(my_game src/main.cpp)
  target_link_libraries(my_game engine)
  target_include_directories(my_game PRIVATE ${CMAKE_SOURCE_DIR})
  ```

---

## Tileset & Tilemap

- **Tileset**: Provide a single atlas texture (e.g., `tileset.png`) and a tile size (e.g., 32). `Tileset` computes source rects by tile ID.
- **Tilemap**: Load CSV layers by name. Example layer workflow (as seen in the demo):
  ```cpp
  // Create tileset
  Texture* tilesTex = assets.getTexture(config.assetRoot + "tileset.png");
  Tileset* tileset = new Tileset(tilesTex, 32);
  scene.getTilemap().setTileset(tileset);

  // Load layers
  scene.getTilemap().loadLayerFromCSV("background", config.assetRoot + "level_bg.csv");
  scene.getTilemap().loadLayerFromCSV("solid",      config.assetRoot + "level_solid.csv");
  scene.getTilemap().loadLayerFromCSV("decoration", config.assetRoot + "level_deco.csv");
  ```
- **Collisions**: Use tilemap collision helpers and/or AABB between `GameObject`s via `CollisionSystem`.

CSV files encode tile IDs per cell. The engine keeps a layer order to render correctly (e.g., background → solid → decoration).

---

## Input

HobbyEngine uses action-based input mapping on SDL scancodes:

```cpp
Input::bind("move_left",  SDL_SCANCODE_A);
Input::bind("move_left",  SDL_SCANCODE_LEFT);
Input::bind("move_right", SDL_SCANCODE_D);
Input::bind("move_right", SDL_SCANCODE_RIGHT);
Input::bind("move_up",    SDL_SCANCODE_W);
Input::bind("move_up",    SDL_SCANCODE_UP);
Input::bind("move_down",  SDL_SCANCODE_S);
Input::bind("move_down",  SDL_SCANCODE_DOWN);
Input::bind("quit",       SDL_SCANCODE_ESCAPE);

// Query
if (Input::isActionPressed("move_left")) { /* ... */ }
```

The `InputSystem` must be updated every frame (this is handled inside `Game::processInput()`).

---

## Rendering & Camera

- `Renderer::clear()` then `Renderer::present()` uses double buffering
- `RenderSystem::drawSprite` draws a sprite at a `Transform` relative to `Camera2D`
- `RenderSystem::drawTilemap` draws all layers in order
- The camera position affects what is visible in the scene

---

## Objects, Movement, Collision

- **GameObject**:
  ```cpp
  GameObject player;
  player.velocity = {100.0f, 0.0f};
  player.sprite   = new Sprite(playerTex, {64.0f, 64.0f});
  player.collider.size = {64.0f, 64.0f};
  scene.addObject(player);
  ```
- **Movement**: Use `MovementSystem::moveX/ moveY` (internally used by scene updates)
- **Collision**: Use tilemap collision resolvers or `CollisionSystem::checkAABB/resolveX/resolveY`

---

## Time

- Call `Time::init()` once, then `Time::update()` per frame
- Use `Time::deltaTime()` for framerate-independent movement

---

## Extending the Engine

- Add new systems in `engine/systems/` and use them from the `Game` update loop
- Extend `GameObject` with additional components as needed
- Add new asset types to `AssetManager` if you want to manage more than textures
- Expand `Tilemap` to support more layer types (e.g., parallax, animated tiles)

---

## Demo

The demo target (`games/demo`) showcases:

- Asset loading (`tileset.png`, `player.png`)
- Tilemap layers (`level_bg.csv`, `level_solid.csv`, `level_deco.csv`)
- Player movement via action bindings
- Rendering flow (clear → draw scene → present)

Run it from the repository root (see Build & Run instructions) so relative asset paths resolve.

---

## Notes & Limitations

- Audio, UI, physics beyond AABB, and advanced resource management are intentionally minimal or not implemented
- Rendering is 2D and sprite/tile-oriented; there is no 3D pipeline
- Asset paths are resolved relative to the current working directory

---

## Contributing

Contributions are welcome. Please keep changes focused and consistent with the existing style:

- Small, modular PRs per subsystem
- Clear commit messages and rationale
- Update documentation when you add or change public APIs

---

## License

License not specified in this repository. Consult the project owner before reuse or distribution.
