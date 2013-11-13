#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include "SDL.h"
#include "Vector.h"

class VisualObject
{
    public:
    Vector pos;

    private:
    SDL_Surface* sprite;
    uint width;
    uint height;

    public:
    VisualObject(Vector pos, SDL_Surface* sprite);
    void draw(SDL_Surface* destination);
    uint w();
    uint h();
};

#endif
