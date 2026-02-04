add_library(engine
    core/Game.cpp
    core/Time.cpp
    core/Scene.cpp
    core/Camera2D.cpp

    systems/InputSystem.cpp
    systems/MovementSystem.cpp
    systems/RenderSystem.cpp
    systems/CollisionSystem.cpp
    systems/InputECSSystem.cpp
    systems/PlayerControlSystem.cpp
    systems/CameraSystem.cpp

    platform/Window.cpp
    platform/Renderer.cpp

    graphics/Texture.cpp
    graphics/AssetManager.cpp
    graphics/Tileset.cpp

    world/Tilemap.cpp

    input/Input.cpp

    ecs/EntityManager.cpp
)

target_include_directories(engine
    PUBLIC ${CMAKE_SOURCE_DIR}
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
target_link_libraries(engine SDL2::SDL2 SDL2_image::SDL2_image)