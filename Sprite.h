#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"

class Sprite
{
    SDL_Surface* sprite;
    int width;
    int height;

    public:
    Sprite(const char*);
    void free();

    void setSprite(SDL_Surface*);
    void setSprite(const char*);
    SDL_Surface* getSprite();

    int w();
    int h();

};

#endif
