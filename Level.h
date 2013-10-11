#ifndef LEVEL_H
#define LEVEL_H

#include "GameObject.h"
#include "Tile.h"
#include "Player.h"
#include "Vector.h"
#include <vector>

struct AABB
{
	Vector min;
	Vector max;

	AABB(Vector min, Vector max);
};

class Level
{
    std::vector<GameObject*> instances;
    std::vector<Tile> tilemap;
    uint width;
    uint height;

    Player* objPlayer;

    public:
    Level(uint width, uint height);
    void loadLevel(std::vector<int> data);
    void step();
    void draw(SDL_Surface* destination);
    bool isTileSolid(int x, int y);
    bool collision_ver(int x, int y, int &tileCoordX);
    bool collision_hor(int x, int y, int &tilecoordy);
    void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
	Vector MinimumTranslationVector(AABB a, AABB b);
	bool AABBIntersection(AABB a, AABB b);
};

#endif
