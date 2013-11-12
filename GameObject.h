#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "VisualObject.h"
#include "SDL.h"
#include "Vector.h"

class GameObject : public VisualObject
{
    public:
    float xVel;
    float yVel;

    private:
    int xStart;
    int yStart;
    int xPrev;
    int yPrev;

    public:
    GameObject(int x, int y, SDL_Surface* sprite);
    virtual void step();
    bool collision(GameObject& obj);
	void reset();
};

#endif
