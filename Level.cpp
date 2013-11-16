#include "Level.h"
#include "ResourceManager.h"
#include "Tile.h"
#include "Vector.h"
#include "Utilities.h"

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

Level::Level(uint width, uint height) : width(width), height(height), objPlayer(NULL) {}

void Level::loadLevel(std::string filename)
{
    std::vector<uint> data;
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (file.is_open())
    {
        //tiles
        uint width = file.get();
        uint height = file.get();
        for (uint y = 0; y < height; y++)
        {
            for (uint x = 0; x < width; x++)
            {
                data.push_back(file.get());
            }
        }

        //solid tiles
        for (uint i = 0; i < file.get(); i++)
        {

        }

        //objects
        for (uint i = 0; i < file.get(); i++)
        {
            uint id = file.get();
            uint x = file.get()*tileSize;
            uint y = file.get()*tileSize;
            if (id == 1)
            {
                objPlayer = new Player(VectorI(x,y), ResourceManager::getSprite(std::string("sprBall")));
                instances.push_back(objPlayer);
            }
        }
        file.close();
    }
}

void Level::step()
{
    for (uint i = 0; i < instances.size(); i++)
    {
        instances.at(i)->step();
    }

	int startx = floor(objPlayer->pos.x / tileSize);
	int endx = floor((objPlayer->pos.x + objPlayer->w()) / tileSize);
	int starty = floor(objPlayer->pos.y / tileSize);
	int endy = floor((objPlayer->pos.y + objPlayer->h()) / tileSize);

	for (uint x = startx; x <= endx; ++x)
	{
		for (uint y = starty; y <= endy; ++y)
		{
			if (isTileSolid(x, y))
			{
				int minx1 = objPlayer->pos.x;
				int maxx1 = objPlayer->pos.x + objPlayer->w();
				int miny1 = objPlayer->pos.y;
				int maxy1 = objPlayer->pos.y + objPlayer->h();

				int minx2 = x * tileSize;
				int maxx2 = x * tileSize + tileSize;
				int miny2 = y * tileSize;
				int maxy2 = y * tileSize + tileSize;

				VectorI mtv = MinimumTranslationVector(AABB(VectorI(minx1, miny1), VectorI(maxx1, maxy1)), AABB(VectorI(minx2, miny2), VectorI(maxx2, maxy2)));
				if (mtv.y < 0)
				{
					objPlayer->onGround = true;
				}
				objPlayer->pos.x += mtv.x;
				objPlayer->pos.y += mtv.y;
			}
		}
	}

	if (isOutsideScreen(objPlayer))
	{
		objPlayer->reset();
	}
}

void Level::draw(SDL_Surface* destination)
{
    for (uint i = 0; i < instances.size(); i++)
    {
        instances.at(i)->draw(destination);
    }
    for (uint i = 0; i < tilemap.size(); i++)
    {
        int x = (i % width)*tileSize;
        int y = floor(i/width)*tileSize;
        if (tilemap.at(i) == 1)
        {
            apply_surface(x, y, ResourceManager::getSprite("sprWall"), destination);
        }
    }
}

void Level::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    if (source != NULL)
    {
        SDL_Rect offset;
        offset.x = x; offset.y = y;
        SDL_BlitSurface(source, NULL, destination, &offset);
    }
}

bool Level::isTileSolid(int x, int y)
{
	int index = x + width*y;
	if (index < tilemap.size())
	{
		return tilemap.isTileSolid(index);
	}
	return false;
}

bool Level::isOutsideScreen(GameObject* obj)
{
	return (obj->pos.x < 0 || obj->pos.x > width*tileSize || obj->pos.y < 0 || obj->pos.y > height*tileSize);
}

VectorI Level::MinimumTranslationVector(AABB a, AABB b)
{
        VectorI amin = a.min;
        VectorI amax = a.max;
        VectorI bmin = b.min;
        VectorI bmax = b.max;

        VectorI mtv;

        float left = bmin.x - amax.x;
        float right = bmax.x - amin.x;
        float top = bmin.y - amax.y;
        float bottom = bmax.y - amin.y;

		if ((left > 0 || right < 0) || (top > 0 || bottom < 0))
		{
			return VectorI(0, 0);
		}

        if (abs(left) < right)
                mtv.x = left;
        else
                mtv.x = right;

        if (abs(top) < bottom)
                mtv.y = top;
        else
                mtv.y = bottom;

        if (abs(mtv.x) < abs(mtv.y))
                mtv.y = 0;
        else
                mtv.x = 0;

		if (mtv.x != 0)
		{
			objPlayer->vel.x = 0;
		}
		if (mtv.y != 0)
		{
			objPlayer->vel.y = 0;
		}
        return mtv;
}

bool Level::isInternalCollision(uint tileI, uint tileJ, VectorI normal)
{
	uint nextTileI = tileI + normal.y;
	uint nextTileJ = tileJ + normal.x;

	return isTileSolid(nextTileI, nextTileJ);
}

AABB::AABB(VectorI min, VectorI max) : min(min), max(max) {}
