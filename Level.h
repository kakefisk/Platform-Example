#ifndef LEVEL_H
#define LEVEL_H

#include "GameObject.h"
#include "Tilemap.h"
#include "Player.h"
#include "Vector.h"
#include <vector>
#include <iostream>

struct AABB
{
	VectorI min;
	VectorI max;

	AABB(VectorI min, VectorI max);
};

class Level
{
    std::vector<GameObject*> instances;
    Tilemap tilemap;
    uint width;
    uint height;
    uint tileSize = 16;

    Player* objPlayer;

    public:
    Level(uint width, uint height);
    void loadLevel(std::string filename);
    void step();
    void draw(SDL_Surface* destination);
    bool isTileSolid(int x, int y);
    void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
	bool isOutsideScreen(GameObject* obj);
	bool isInternalCollision(uint tileI, uint tileJ, VectorI normal);
	VectorI MinimumTranslationVector(AABB a, AABB b);
	bool AABBIntersection(AABB a, AABB b);
};

#endif
