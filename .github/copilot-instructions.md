# Copilot Instructions for `my_engine`

These guidelines help Copilot (and contributors) generate consistent, minimal, and correct changes for this C++ SDL2 game engine and the demo game.

## Assistant Behavior
- Be concise, direct, and friendly. Prefer actionable guidance.
- If asked about the model, state you are using GPT-5.
- Follow Microsoft content policies; never generate harmful, hateful, racist, sexist, lewd, or violent content.
- Avoid copyrighted content unless provided by the user in this repo.

## Coding Style
- Language: C++ (compatible with the project’s current toolchain).
- Headers use `#pragma once`; prefer this over include guards.
- Indentation: 4 spaces. Braces on next line (Allman style):
  ```cpp
  class Example
  {
  public:
      void run();
  };
  ```
- Class names and methods use PascalCase/CamelCase like `Game`, `run()`, `getScene()`.
- Prefer direct, simple member names (no trailing underscores), e.g., `running`, `window`.
- Includes use project-root include paths (configured via `target_include_directories(engine PUBLIC ${CMAKE_SOURCE_DIR})`):
  ```cpp
  #include <engine/core/Scene.h>
  #include <engine/ecs/World.h>
  #include <engine/systems/RenderSystem.h>
  ```
- Forward-declare external types where practical (e.g., `struct SDL_Renderer;`) in headers.
- Avoid inline comments unless explicitly requested.
- Do not add license headers.
- Do not use one-letter variable names unless explicitly requested.

## Project Structure
- Engine library sources: see [engine/CMakeLists.txt](engine/CMakeLists.txt). Key areas:
  - Core: [engine/core](engine/core) (e.g., `Game`, `Scene`, `Camera2D`, `Time`)
  - ECS: [engine/ecs](engine/ecs) (entities, components, `World`)
  - Systems: [engine/systems](engine/systems) (e.g., `RenderSystem`, `MovementSystem`, `CollisionSystem`)
  - Graphics: [engine/graphics](engine/graphics)
  - Platform: [engine/platform](engine/platform)
  - World: [engine/world](engine/world)
  - Input: [engine/input](engine/input)
- Demo game: [games/demo](games/demo) links against `engine`.

## CMake & Build
- The engine builds as a library and links with SDL2/SDL2_image.
- When adding new engine sources, append them to `add_library(engine ...)` in [engine/CMakeLists.txt](engine/CMakeLists.txt).
- Keep public headers under `engine/` with include paths consistent with existing files.
- Quick build/run:
  ```bash
  mkdir -p build
  cd build
  cmake ..
  make -j
  ./games/demo/demo
  ```

## ECS Guidelines
- Entities: created/destroyed via `World` (see [engine/ecs/World.h](engine/ecs/World.h)).
- Components: simple `struct`s under [engine/ecs/components](engine/ecs/components). Store state only.
- Storage: `ComponentStorage<T>` manages add/has/get/remove.
- `World` holds explicit storages and template specializations for `getStorage<T>()`.
- To add a new component type:
  1. Create `engine/ecs/components/YourComponent.h` with `#pragma once` and a plain `struct YourComponent { ... };`.
  2. Add `ComponentStorage<YourComponent> yourComponents;` to `World`.
  3. Add template specializations for `getStorage<YourComponent>()` (both non-const and const) in `World.h`.
  4. Update systems to read/write `YourComponent` as needed.

## Systems
- Place new systems in [engine/systems](engine/systems).
- Prefer stateless, pure-style functions or static methods operating on component data (e.g., `RenderSystem` uses static functions taking `SDL_Renderer*`, `Transform`, `Sprite`, `Camera2D`).
- Systems must not own state long-term; read from `World` and operate per-frame.

## Rendering & Assets
- Rendering flows through `Window` and `Renderer` (see [engine/platform](engine/platform)).
- Use `RenderSystem` helpers to draw sprites, rectangles, colliders, and tilemaps (see [engine/systems/RenderSystem.h](engine/systems/RenderSystem.h)).
- Assets are managed via `AssetManager` (see [engine/graphics/AssetManager.h](engine/graphics/AssetManager.h)).

## Scene & Game Loop
- `Game` owns `Window`, `Renderer`, `AssetManager`, and `Scene` (see [engine/core/Game.h](engine/core/Game.h)).
- `Scene` holds `objects`, `camera`, and `tilemap` with `update(deltaTime)` and `render(SDL_Renderer*)` (see [engine/core/Scene.h](engine/core/Scene.h)).
- Keep `processInput()`, `update()`, and `render()` responsibilities separated when extending the game loop.

## Input
- Input utilities live under [engine/input](engine/input). Use or extend `Input` and ECS `InputIntent` component for gameplay logic.

## Demo Game Changes
- Add demo-side logic in [games/demo/src](games/demo/src), keeping engine reusable and generic.
- Link against `engine` only; avoid demo-specific code inside engine.

## Testing & Verification
- Prefer small, focused changes. Fix root causes rather than superficial patches.
- After edits, build the project and run the demo.
- If you modify public APIs, update affected call sites in both engine and demo.

## Copilot Prompts (What to Ask For)
- “Add a new `YourComponent` to ECS with storage & `World` specializations.”
- “Create `YourSystem` in `engine/systems` that updates `Velocity` from `InputIntent`.”
- “Add a tilemap loader helper in `world/Tilemap.cpp` and expose a minimal API.”
- “Extend `Scene::update` to invoke `MovementSystem` and `CollisionSystem`.”
- “Wire a new sprite asset via `AssetManager` and draw it in `RenderSystem`.”

## Do / Don’t
- Do: Keep changes minimal and consistent with existing style.
- Do: Update CMake sources lists when adding files.
- Do: Prefer pure functions/static methods in systems; pass data explicitly.
- Don’t: Change unrelated files or refactor broadly without need.
- Don’t: Add license headers or excessive inline comments.
- Don’t: Introduce one-letter variable names.

## Quick References
- Engine CMake: [engine/CMakeLists.txt](engine/CMakeLists.txt)
- Core: [engine/core](engine/core)
- ECS: [engine/ecs](engine/ecs), components: [engine/ecs/components](engine/ecs/components)
- Systems: [engine/systems](engine/systems)
- Graphics: [engine/graphics](engine/graphics)
- Platform: [engine/platform](engine/platform)
- World: [engine/world](engine/world)
- Demo: [games/demo](games/demo)
