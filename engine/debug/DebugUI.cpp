#include "DebugUI.h"

#include <engine/vendor/imgui/imgui.h>
#include <engine/vendor/imgui/backends/imgui_impl_sdl2.h>
#include <engine/vendor/imgui/backends/imgui_impl_sdlrenderer2.h>

static SDL_Renderer* s_renderer = nullptr;
static bool s_initialized = false;

void DebugUI::init(SDL_Window* window, SDL_Renderer* renderer)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    s_renderer = renderer;
    s_initialized = true;
}

void DebugUI::shutdown()
{
    if (!s_initialized) return;

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    s_renderer = nullptr;
    s_initialized = false;
}

void DebugUI::beginFrame()
{
    if (!s_initialized) return;

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void DebugUI::draw(World& world)
{
    if (!s_initialized) return;

    ImGui::Begin("Debug");
    ImGui::Text("Transforms: %zu", world.transforms.size());
    ImGui::Text("Velocities: %zu", world.velocities.size());
    ImGui::Text("Colliders:  %zu", world.colliders.size());
    ImGui::Text("Sprites:    %zu", world.sprites.size());
    ImGui::Text("Camera Targets:    %zu", world.cameraTargets.size());
    ImGui::Text("Camera Offsets:    %zu", world.cameraOffsets.size());
    ImGui::Text("Input Intent:    %zu", world.inputIntents.size());
    ImGui::End();
}

void DebugUI::endFrame()
{
    if (!s_initialized) return;

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(
        ImGui::GetDrawData(),
        s_renderer
    );
}
