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
			if (isTileSolid(x, y))
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
				if (mtv.y < 0)
				{
					objPlayer->onGround = true;
				}
				objPlayer->x += mtv.x;
				objPlayer->y += mtv.y;
			}
		}
	}

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
			objPlayer->xVel = 0;
		}
		if (mtv.y != 0)
		{
			objPlayer->yVel = 0;
		}
        return mtv;
}

bool Level::isInternalCollision(int tileI, int tileJ, Vector normal)
{
	int nextTileI = tileI + normal.y;
	int nextTileJ = tileJ + normal.x;

	return isTileSolid(nextTileI, nextTileJ);
}

/*Vector MTV(GameObject &a, GameObject &b)
{
        Vector amin = Vector(a.x, a.y);
        Vector amax = Vector(a.x + a.w, a.y + a.h);
 
        Vector bmin = Vector(b.x, b.y);
        Vector bmax = Vector(b.x + b.w, b.y + b.h);
 
        float left   = bmin.x - amax.x;
        float right  = bmax.x - amin.x;
        float top    = bmin.y - amax.y;
        float bottom = bmax.y - amin.y;
 
        if ( ( left > 0 || right < 0 ) || ( top > 0 || bottom < 0 ) )
                return Vector( 0.0f, 0.0f );
 
        Vector mtv;
 
        if ( fabsf( left ) < right )
                mtv.x = left;
        else
                mtv.x = right;
 
        if ( fabsf( top ) < bottom )
                mtv.y = top;
        else
                mtv.y = bottom;
 
        if ( fabsf( mtv.x ) < fabsf( mtv.y ) )
                mtv.y = 0;
        else
                mtv.x = 0;
 
        return mtv;
}*/

AABB::AABB(Vector min, Vector max) : min(min), max(max) {}