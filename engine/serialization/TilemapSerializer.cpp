#include "TilemapSerializer.h"

#include <engine/vendor/json/json.hpp>
#include <fstream>

using json = nlohmann::json;

bool TilemapSerializer::save(const Tilemap &tilemap,
                             const std::string &path)
{
    json root;

    root["tileSize"] = tilemap.getTileSize();
    root["width"] = tilemap.getWidth();
    root["height"] = tilemap.getHeight();
    root["layerOrder"] = tilemap.getLayerOrder();

    json layersJson;

    for (const auto &[name, layer] : tilemap.getLayers())
    {
        json layerJson;

        for (int y = 0; y < tilemap.getHeight(); ++y)
        {
            json row;
            for (int x = 0; x < tilemap.getWidth(); ++x)
            {
                row.push_back(
                    tilemap.getTile(name, x, y)
                );
            }
            layerJson.push_back(row);
        }

        layersJson[name] = layerJson;
    }

    root["layers"] = layersJson;

    std::ofstream file(path);
    if (!file.is_open())
        return false;

    file << root.dump(4);
    return true;
}

bool TilemapSerializer::load(Tilemap &tilemap,
                             const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
        return false;

    json root;
    file >> root;

    tilemap.clear();

    int width = root["width"];
    int height = root["height"];

    tilemap.resize(width, height);

    for (const auto &layerName : root["layerOrder"])
    {
        tilemap.createLayer(layerName);

        const auto &layerData = root["layers"][layerName];

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                tilemap.setTile(
                    layerName,
                    x,
                    y,
                    layerData[y][x]
                );
            }
        }
    }

    return true;
}


