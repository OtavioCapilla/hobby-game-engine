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

    debug/DebugUI.cpp
    debug/ECSInspector.cpp
)

target_include_directories(engine PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/engine/vendor/imgui
    ${CMAKE_SOURCE_DIR}/engine/vendor/imgui/backends
)

target_sources(engine PRIVATE
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/backends/imgui_impl_sdl2.cpp
    vendor/imgui/backends/imgui_impl_sdlrenderer2.cpp
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
target_link_libraries(engine SDL2::SDL2 SDL2_image::SDL2_image)