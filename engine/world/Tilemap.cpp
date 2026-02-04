#include "Tilemap.h"

#include <fstream>
#include <sstream>
#include <iostream>

Tilemap::Tilemap(int size)
    : tileSize(size),
      width(0),
      height(0),
      tileset(nullptr)
{
}

bool Tilemap::loadCSV(const std::string &path,
                      std::vector<int> &outTiles,
                      int &outWidth,
                      int &outHeight)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open CSV: " << path << "\n";
        return false;
    }

    std::string line;
    int detectedWidth = -1;
    int detectedHeight = 0;

    outTiles.clear();

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string cell;
        int colCount = 0;

        while (std::getline(ss, cell, ','))
        {
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

bool Tilemap::loadLayerFromCSV(const std::string &layerName,
                               const std::string &filePath)
{
    std::vector<int> tiles;
    int w = 0, h = 0;

    if (!loadCSV(filePath, tiles, w, h))
    {
        std::cerr << "Failed loading layer: " << layerName << "\n";
        return false;
    }

    if (layers.empty())
    {
        width = w;
        height = h;
    }
    else if (w != width || h != height)
    {
        std::cerr << "Layer size mismatch\n";
        return false;
    }

    layers[layerName] = {tiles};
    layerOrder.push_back(layerName);
    return true;
}

int Tilemap::getWidth() const { return width; }
int Tilemap::getHeight() const { return height; }
int Tilemap::getTileSize() const { return tileSize; }

bool Tilemap::isInside(int x, int y) const
{
    return x >= 0 && y >= 0 && x < width && y < height;
}

int Tilemap::getTile(const std::string &layer,
                     int x, int y) const
{
    const auto &tiles = layers.at(layer).tiles;
    return tiles[y * width + x];
}

Vector2 Tilemap::tileToWorld(int x, int y) const
{
    return {(float)(x * tileSize), (float)(y * tileSize)};
}

void Tilemap::setTileset(Tileset *ts) { tileset = ts; }
const Tileset *Tilemap::getTileset() const { return tileset; }

const std::vector<std::string> &Tilemap::getLayerOrder() const
{
    return layerOrder;
}

const std::unordered_map<std::string, Tilemap::Layer> &
Tilemap::getLayers() const
{
    return layers;
}

void Tilemap::clear()
{
    layers.clear();
    layerOrder.clear();
    width = 0;
    height = 0;
}

void Tilemap::createLayer(const std::string &name)
{
    if (layers.find(name) != layers.end())
        return;

    Layer layer;
    layer.tiles.resize(width * height, 0);

    layers[name] = layer;
    layerOrder.push_back(name);
}

void Tilemap::setTile(const std::string &layer,
                      int x, int y, int value)
{
    if (!isInside(x, y))
        return;

    layers.at(layer).tiles[y * width + x] = value;
}

void Tilemap::resize(int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;

    for (auto &[name, layer] : layers)
    {
        layer.tiles.clear();
        layer.tiles.resize(width * height, 0);
    }
}
