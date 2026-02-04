#include "SceneSerializer.h"

#include <engine/serialization/TilemapSerializer.h>
#include <engine/serialization/WorldSerializer.h>

#include <engine/vendor/json/json.hpp>
#include <fstream>

using json = nlohmann::json;

bool SceneSerializer::save(const Scene& scene,
                           const std::string& path)
{
    json root;
    json sceneJson;

    const Camera2D& cam = scene.getCamera();

    sceneJson["camera"] = {
        { "position", { cam.getPosition().x, cam.getPosition().y } },
        { "zoom", cam.getZoom() }
    };

    json tilemapJson;
    TilemapSerializer::save(scene.getTilemap(), tilemapJson);
    sceneJson["tilemap"] = tilemapJson;

    json ecsJson;
    WorldSerializer::save(scene.getWorld(), ecsJson);
    sceneJson["ecs"] = ecsJson;

    root["scene"] = sceneJson;

    std::ofstream file(path);
    if (!file.is_open())
        return false;

    file << root.dump(4);
    return true;
}

bool SceneSerializer::load(Scene& scene,
                           const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
        return false;

    json root;
    file >> root;

    const json& sceneJson = root["scene"];

    scene.clear();

    auto camJson = sceneJson["camera"];
    scene.getCamera().setPosition({
        camJson["position"][0],
        camJson["position"][1]
    });
    scene.getCamera().setZoom(camJson["zoom"]);

    TilemapSerializer::load(
        scene.getTilemap(),
        sceneJson["tilemap"]
    );

    WorldSerializer::load(
        scene.getWorld(),
        sceneJson["ecs"]
    );

    return true;
}
