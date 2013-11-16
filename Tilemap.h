#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <cstddef>

class Tilemap
{
	std::vector<uint> map;
	std::vector<uint> solidTiles;
	uint tileSize;
	uint width;
	uint height;

	public:
	Tilemap();
	Tilemap(uint w, uint h, std::vector<uint> data);
	void setSize(uint w, uint h);
	void setMapData(std::vector<uint> data);
	std::vector<uint>* getMap();
	uint getCol(uint i);
    uint getRow(uint i);
    uint getIndex(uint x, uint y);
	void setSolidTiles(std::vector<uint> data);
	bool isTileSolid(uint x, uint y);
	bool isTileSolid(uint index);
	uint size();
	uint at(uint index);
};

#endif
