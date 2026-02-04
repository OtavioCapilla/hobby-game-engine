#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <engine/math/Vector2.h>
#include <engine/graphics/Tileset.h>
#include <engine/core/GameObject.h>

class Tilemap {
public:
    explicit Tilemap(int tileSize);

    bool loadLayerFromCSV(const std::string& layerName,
                          const std::string& filePath);

    const std::vector<std::string>& getLayerOrder() const;

    int getTile(const std::string& layer,
                int x, int y) const;

    int getWidth() const;
    int getHeight() const;
    int getTileSize() const;
    bool isInside(int x, int y) const;

    Vector2 tileToWorld(int x, int y) const;

    void setTileset(Tileset* tileset);
    const Tileset* getTileset() const;

private:
    struct Layer {
        std::vector<int> tiles;
    };

    bool loadCSV(const std::string& path,
                 std::vector<int>& outTiles,
                 int& outWidth,
                 int& outHeight);

private:
    int tileSize;
    int width;
    int height;

    std::unordered_map<std::string, Layer> layers;
    std::vector<std::string> layerOrder;

    Tileset* tileset;
};
