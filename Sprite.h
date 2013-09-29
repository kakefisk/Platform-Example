#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"

class Sprite
{
    SDL_Surface* sprite;
    uint width;
    uint height;

    public:
    Sprite(const char* filename);
    void free();

    void setSprite(SDL_Surface* destination);
    void setSprite(const char* filename);
    SDL_Surface* getSprite();

    uint w();
    uint h();

};

#endif
