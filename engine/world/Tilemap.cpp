#include "Tilemap.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <engine/systems/CollisionSystem.h>

// =======================
// CONSTRUTOR
// =======================
Tilemap::Tilemap(int size)
    : tileSize(size),
      width(0),
      height(0),
      tileset(nullptr)
{
}

// =======================
// CSV LOADER INTERNO
// =======================
bool Tilemap::loadCSV(const std::string& path,
                      std::vector<int>& outTiles,
                      int& outWidth,
                      int& outHeight)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open CSV: " << path << "\n";
        return false;
    }

    std::string line;
    int detectedWidth = -1;
    int detectedHeight = 0;

    outTiles.clear();

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string cell;
        int colCount = 0;

        while (std::getline(ss, cell, ',')) {
            outTiles.push_back(std::stoi(cell));
            colCount++;
        }

        if (detectedWidth == -1)
            detectedWidth = colCount;
        else if (colCount != detectedWidth)
            return false;

        detectedHeight++;
    }

    outWidth = detectedWidth;
    outHeight = detectedHeight;
    return true;
}

// =======================
// LOAD LAYER
// =======================
bool Tilemap::loadLayerFromCSV(const std::string& layerName,
                               const std::string& filePath)
{
    std::vector<int> tiles;
    int w = 0, h = 0;

    if (!loadCSV(filePath, tiles, w, h)) {
        std::cerr << "Failed loading layer: " << layerName << "\n";
        return false;
    }

    if (layers.empty()) {
        width = w;
        height = h;
    } else if (w != width || h != height) {
        std::cerr << "Layer size mismatch\n";
        return false;
    }

    layers[layerName] = { tiles };
    layerOrder.push_back(layerName);
    return true;
}

// =======================
// GETTERS
// =======================
int Tilemap::getWidth() const { return width; }
int Tilemap::getHeight() const { return height; }
int Tilemap::getTileSize() const { return tileSize; }

bool Tilemap::isInside(int x, int y) const {
    return x >= 0 && y >= 0 && x < width && y < height;
}

int Tilemap::getTile(const std::string& layer,
                     int x, int y) const
{
    const auto& tiles = layers.at(layer).tiles;
    return tiles[y * width + x];
}

Vector2 Tilemap::tileToWorld(int x, int y) const {
    return { (float)(x * tileSize), (float)(y * tileSize) };
}

// =======================
// TILESET
// =======================
void Tilemap::setTileset(Tileset* ts) { tileset = ts; }
const Tileset* Tilemap::getTileset() const { return tileset; }

const std::vector<std::string>& Tilemap::getLayerOrder() const {
    return layerOrder;
}

// =======================
// COLISÃO (SÓ CAMADA "solid")
// =======================
void Tilemap::resolveCollisionsX(GameObject& obj) const
{
    if (!layers.count("solid")) return;

    int ts = tileSize;
    float px = obj.transform.position.x;
    float py = obj.transform.position.y;
    float pw = obj.collider.size.x;
    float ph = obj.collider.size.y;

    int minX = (int)(px / ts);
    int maxX = (int)((px + pw) / ts);
    int minY = (int)(py / ts);
    int maxY = (int)((py + ph) / ts);

    const auto& tiles = layers.at("solid").tiles;

    for (int y = minY; y <= maxY; ++y)
        for (int x = minX; x <= maxX; ++x) {
            if (!isInside(x, y)) continue;
            if (tiles[y * width + x] == 0) continue;

            GameObject tile;
            tile.transform.position = tileToWorld(x, y);
            tile.collider.size = { (float)ts, (float)ts };

            if (CollisionSystem::checkAABB(obj, tile))
                CollisionSystem::resolveX(obj, tile);
        }
}

void Tilemap::resolveCollisionsY(GameObject& obj) const
{
    if (!layers.count("solid")) return;

    int ts = tileSize;
    float px = obj.transform.position.x;
    float py = obj.transform.position.y;
    float pw = obj.collider.size.x;
    float ph = obj.collider.size.y;

    int minX = (int)(px / ts);
    int maxX = (int)((px + pw) / ts);
    int minY = (int)(py / ts);
    int maxY = (int)((py + ph) / ts);

    const auto& tiles = layers.at("solid").tiles;

    for (int y = minY; y <= maxY; ++y)
        for (int x = minX; x <= maxX; ++x) {
            if (!isInside(x, y)) continue;
            if (tiles[y * width + x] == 0) continue;

            GameObject tile;
            tile.transform.position = tileToWorld(x, y);
            tile.collider.size = { (float)ts, (float)ts };

            if (CollisionSystem::checkAABB(obj, tile))
                CollisionSystem::resolveY(obj, tile);
        }
}
