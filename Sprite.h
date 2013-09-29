#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include <string>

class Sprite
{
    SDL_Surface* sprite;
    int width;
    int height;

    public:
    Sprite(std::string);
    ~Sprite();

    void setSprite(SDL_Surface*);
    void setSprite(std::string);
    SDL_Surface* getSprite();

    int w();
    int h();

};

#endif
