#ifndef LEVEL_H
#define LEVEL_H

#include "GameObject.h"
#include <vector>

class Level
{
    std::vector<GameObject*> instances;
    uint width;
    uint height;

    public:
    Level(uint width, uint height);
    void loadLevel(std::vector<int> data);
    void step();
    void draw(SDL_Surface* destination);
};

#endif
