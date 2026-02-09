#include "TilemapSerializer.h"

#include <engine/vendor/json/json.hpp>
#include <fstream>

using json = nlohmann::json;

void TilemapSerializer::save(const Tilemap &tilemap,
                             nlohmann::json &out)
{
    out["tileSize"] = tilemap.getTileSize();
    out["width"] = tilemap.getWidth();
    out["height"] = tilemap.getHeight();
    out["layerOrder"] = tilemap.getLayerOrder();

    nlohmann::json layersJson;

    for (const auto &name : tilemap.getLayerOrder())
    {
        const auto &layer = tilemap.getLayers().at(name);

        nlohmann::json layerJson;

        for (int y = 0; y < tilemap.getHeight(); ++y)
        {
            nlohmann::json row;
            for (int x = 0; x < tilemap.getWidth(); ++x)
            {
                row.push_back(
                    tilemap.getTile(name, x, y));
            }
            layerJson.push_back(row);
        }

        layersJson[name] = layerJson;
    }

    out["layers"] = layersJson;
}

void TilemapSerializer::load(Tilemap &tilemap,
                             const nlohmann::json &in)
{
    tilemap.clear();

    int width = in["width"];
    int height = in["height"];

    tilemap.resize(width, height);

    for (const auto &layerName : in["layerOrder"])
    {
        tilemap.createLayer(layerName);

        const auto &layerData = in["layers"][layerName];

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                tilemap.setTile(
                    layerName,
                    x,
                    y,
                    layerData[y][x]);
            }
        }
    }
}
