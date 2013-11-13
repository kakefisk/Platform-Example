#include "Level.h"
#include "ResourceManager.h"
#include "Tile.h"
#include "Vector.h"

#include <iostream>
#include <cmath>
#include <string>

int tileSize = 16;

Level::Level(uint width, uint height) : width(width), height(height), objPlayer(NULL) {}

void Level::loadLevel(std::vector<int> data)
{
    for (uint i = 0; i < data.size(); i++)
    {
        int x = (i % width)*tileSize;
        int y = floor(i/width)*tileSize;
        if (data.at(i) == 1)
        {
            tilemap.push_back(Tile(1, true));
        }
        else if (data.at(i) == 2)
        {
            objPlayer = new Player(Vector(x,y), ResourceManager::getSprite(std::string("sprBall")));
            instances.push_back(objPlayer);
            tilemap.push_back(Tile(0, false));
        }
        else
        {
            tilemap.push_back(Tile(0, false));
        }
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

				Vector mtv = MinimumTranslationVector(AABB(Vector(minx1, miny1), Vector(maxx1, maxy1)), AABB(Vector(minx2, miny2), Vector(maxx2, maxy2)));
				if (mtv.y < 0)
				{
					objPlayer->onGround = true;
				}
				objPlayer->pos += mtv;
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
        if (tilemap.at(i).id == 1)
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
		return tilemap.at(index).solid;
	}
	return false;
}

bool Level::isOutsideScreen(GameObject* obj)
{
	return (obj->pos.x < 0 || obj->pos.x > width*tileSize || obj->pos.y < 0 || obj->pos.y > height*tileSize);
}

Vector Level::MinimumTranslationVector(AABB a, AABB b)
{
        Vector amin = a.min;
        Vector amax = a.max;
        Vector bmin = b.min;
        Vector bmax = b.max;
     
        Vector mtv;
     
        float left = bmin.x - amax.x;
        float right = bmax.x - amin.x;
        float top = bmin.y - amax.y;
        float bottom = bmax.y - amin.y;

		if ((left > 0 || right < 0) || (top > 0 || bottom < 0))
		{
			return Vector(0, 0);
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

bool Level::isInternalCollision(int tileI, int tileJ, Vector normal)
{
	int nextTileI = tileI + normal.y;
	int nextTileJ = tileJ + normal.x;

	return isTileSolid(nextTileI, nextTileJ);
}

AABB::AABB(Vector min, Vector max) : min(min), max(max) {}