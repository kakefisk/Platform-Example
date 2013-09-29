#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "sprite.h"

class GameObject
{
    public:
    int x;
    int y;
    int xVel;
    int yVel;

    private:
    Sprite sprite;
    int xStart;
    int yStart;
    int xPrev;
    int yPrev;

    public:
    GameObject(int, int, const char*);
    virtual void step();
    void draw(SDL_Surface*);
    bool collision(GameObject&);
};

#endif
