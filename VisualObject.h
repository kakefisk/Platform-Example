#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include "SDL.h"

class VisualObject
{
    public:
    int x;
    int y;

    private:
    SDL_Surface* sprite;
    uint width;
    uint height;

    public:
    VisualObject(int x, int y, SDL_Surface* sprite);
    void draw(SDL_Surface* destination);
    uint w();
    uint h();
};

#endif
