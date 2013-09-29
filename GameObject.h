#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL.h"

class GameObject
{
    public:
    int x;
    int y;
    int xVel;
    int yVel;

    private:
    SDL_Surface* sprite;
    uint width;
    uint height;
    int xStart;
    int yStart;
    int xPrev;
    int yPrev;

    public:
    GameObject(int x, int y, SDL_Surface* sprite);
    virtual void step();
    void draw(SDL_Surface* destination);
    bool collision(GameObject& obj);
    uint w();
    uint h();
};

#endif
