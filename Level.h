#ifndef LEVEL_H
#define LEVEL_H

#include "GameObject.h"
#include "Tile.h"
#include "Player.h"
#include "Vector.h"
#include <vector>

struct AABB
{
	VectorI min;
	VectorI max;

	AABB(VectorI min, VectorI max);
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
    void loadLevel(std::string data);
    void step();
    void draw(SDL_Surface* destination);
    bool isTileSolid(int x, int y);
    void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
	bool isOutsideScreen(GameObject* obj);
	bool isInternalCollision(int tileI, int tileJ, VectorI normal);
	VectorI MinimumTranslationVector(AABB a, AABB b);
	bool AABBIntersection(AABB a, AABB b);
};

#endif
