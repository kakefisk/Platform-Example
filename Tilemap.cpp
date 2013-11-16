#include "Tilemap.h"
#include "Utilities.h"

#include <cmath>

Tilemap::Tilemap() : width(0), height(0) {}

Tilemap::Tilemap(uint w, uint h, std::vector<uint> data) : map(data), width(w), height(h) {}

void Tilemap::setMapData(std::vector<uint> data)
{
    map = data;
}

std::vector<uint>* Tilemap::getMap()
{
    return &map;
}

uint Tilemap::size()
{
    return width*height;
}

uint Tilemap::at(uint index)
{
    return map.at(index);
}

void Tilemap::setSolidTiles(std::vector<uint> data)
{
    solidTiles = data;
}

void Tilemap::setSize(uint w, uint h)
{
    width = w;
    height = h;
}

uint Tilemap::getCol(uint i)
{
    return i % width;
}

uint Tilemap::getRow(uint i)
{
    return floor(i/width);
}

uint Tilemap::getIndex(uint x, uint y)
{
    return x + width*y;
}

bool Tilemap::isTileSolid(uint index)
{
    return util::contains(solidTiles, map.at(index));
}

bool Tilemap::isTileSolid(uint x, uint y)
{
    return isTileSolid(getIndex(x, y));
}
