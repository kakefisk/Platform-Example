#ifndef LEVEL_H
#define LEVEL_H

#include "GameObject.h"
#include <vector>

class Level
{
    std::vector<GameObject> instances;
    int width;
    int height;

    public:
    Level(int, int);
    void loadLevel(int[]);
    void step();
    void draw(SDL_Surface*);
};

#endif
