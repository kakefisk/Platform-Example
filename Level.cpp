#include "Level.h"
#include "ResourceManager.h"
#include "Tile.h"
#include "Vector.h"

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
            objPlayer = new Player(x, y, ResourceManager::getSprite(std::string("sprBall")));
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

	int startx = floor(objPlayer->x / tileSize);
	int endx = floor((objPlayer->x + objPlayer->w()) / tileSize);
	int starty = floor(objPlayer->y / tileSize);
	int endy = floor((objPlayer->y + objPlayer->h()) / tileSize);

	for (uint x = startx; x <= endx; ++x)
	{
		for (uint y = starty; y <= endy; ++y)
		{
			int minx1 = objPlayer->x;
			int maxx1 = objPlayer->x + objPlayer->w();
			int miny1 = objPlayer->y;
			int maxy1 = objPlayer->y + objPlayer->h();

			int minx2 = x * tileSize;
			int maxx2 = x * tileSize + tileSize;
			int miny2 = y * tileSize;
			int maxy2 = y * tileSize + tileSize;

			Vector mtv = MinimumTranslationVector(AABB(Vector(minx1, miny1), Vector(maxx1, maxy1)), AABB(Vector(minx2, miny2), Vector(maxx2, maxy2)));
			objPlayer->x += mtv.x;
			objPlayer->y += mtv.y;
		}
	}

	/*// Test for collision with the objPlayer and the world by finding the overlapping tiles first
	int startx = floor(objPlayer->x / tileSize);
	int endx = floor((objPlayer->x + objPlayer->w()) / tileSize);
	int starty = floor(objPlayer->y / tileSize);
	int endy = floor((objPlayer->y + objPlayer->h()) / tileSize);

	// Find the minimum translation distance
	for (uint x = startx; x <= endx; ++x)
	{
		for (uint y = starty; y <= endy; ++y)
		{
			if (isTileSolid(x, y))
			{
				Vector result;

				int minx1 = objPlayer->x;
				int maxx1 = objPlayer->x + objPlayer->w();
				int miny1 = objPlayer->y;
				int maxy1 = objPlayer->y + objPlayer->h();

				int minx2 = x * tileSize;
				int maxx2 = x * tileSize + tileSize;
				int miny2 = y * tileSize;
				int maxy2 = y * tileSize + tileSize;

				if (maxx1 < minx2 || minx1 > maxx2 || maxy1 < miny2 || miny1 > maxy2)
				{
					continue;
				}

				// Finds the shallow way out
				Vector mtd;
				mtd.x = maxx1 - minx2 < maxx2 - minx1 ? minx2 - maxx1 : maxx2 - minx1;
				mtd.y = maxy1 - miny2 < maxy2 - miny1 ? miny2 - maxy1 : maxy2 - miny1;
				if (abs(mtd.x) < abs(mtd.y))
				{
					mtd.y = 0;
				}
				else
				{
					mtd.x = 0;
				}

				if (mtd.x != 0)
				{
					objPlayer->xVel = 0;
				}
				if (mtd.y != 0)
				{
					objPlayer->yVel = 0;
				}
				if (mtd.y < 0) // If player has been moved up -> on the ground
				{
					objPlayer->onGround = true;
				}
				objPlayer->x += mtd.x;
				objPlayer->y += mtd.y;
			}
		}
	}*/

	/*std::vector<Vector> overlapTiles;
	int mtdX = INT_MAX;
	int mtdY = INT_MAX;
	for (int x = floor((objPlayer->x - objPlayer->w() / 2) / tileSize); x <= floor((objPlayer->x + objPlayer->w() / 2) / tileSize); ++x)
	{
		for (int y = floor((objPlayer->y - objPlayer->h() / 2) / tileSize); y <= floor((objPlayer->y + objPlayer->h() / 2) / tileSize); ++y)
		{
			if (isTileSolid(x, y))
			{
				overlapTiles.push_back(Vector(x, y));
				int xResult1 = x * tileSize - (objPlayer->x + objPlayer->w() / 2);
				int xResult2 = (x * tileSize + tileSize) - (objPlayer->x - objPlayer->w() / 2);
				int yResult1 = y * tileSize - (objPlayer->y + objPlayer->h() / 2);
				int yResult2 = (y * tileSize + tileSize) - (objPlayer->y - objPlayer->h() / 2);
				int overlapX = abs(xResult1) < abs(xResult2) ? xResult1 : xResult2;
				int overlapY = abs(yResult1) < abs(yResult2) ? yResult1 : yResult2;
				if (abs(overlapX) < abs(mtdX))
				{
					mtdX = overlapX;
				}
				if (abs(overlapY) < abs(mtdY))
				{
					mtdY = overlapY;
				}
			}
		}
	}

	if (overlapTiles.size() == 0)
	{
		// No overlapping tiles
	}
	else if (overlapTiles.size() == 1)
	{
        // Case 1
        if (abs(mtdX) < abs(mtdY))
		{
			objPlayer->x += mtdX;
			objPlayer->xVel = 0;
		}
		else
		{
			objPlayer->y += mtdY;
			objPlayer->yVel = 0;
		}
	}
	else if (overlapTiles.size() == 3 || abs(overlapTiles.at(0).x - overlapTiles.at(1).x) == abs(overlapTiles.at(0).y - overlapTiles.at(1).y))
	{
		// Case 3
		objPlayer->x += mtdX;
		objPlayer->y += mtdY;
		objPlayer->xVel = 0;
		objPlayer->yVel = 0;
	}
	else if (overlapTiles.size() == 2)
	{
		// Case 2
		if (overlapTiles.at(0).x == overlapTiles.at(1).x)
		{
			objPlayer->x += mtdX;
			objPlayer->xVel = 0;
		}
		else
		{
			objPlayer->y += mtdY;
			objPlayer->yVel = 0;
		}
	}*/

	if (objPlayer->x < 0 || objPlayer->x > width*tileSize || objPlayer->y < 0 || objPlayer->y > height*tileSize)
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
     
        return mtv;
}

bool Level::AABBIntersection(AABB a, AABB b)
{
        if (a.max.x < b.min.x)
                return false;
        if (a.max.y < b.min.y)
                return false;
        if (a.min.x > b.max.x)
                return false;
        if (a.min.x > b.max.x)
                return false;
     
        return true;
}

AABB::AABB(Vector min, Vector max) : min(min), max(max) {}