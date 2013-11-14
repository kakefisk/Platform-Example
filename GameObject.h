#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "VisualObject.h"
#include "SDL.h"
#include "Vector.h"

class GameObject : public VisualObject
{
    public:
    VectorF vel;

    private:
    VectorI startPos;
    VectorI prevPos;

    public:
    GameObject(VectorI pos, SDL_Surface* sprite);
    virtual void step();
    bool collision(GameObject& obj);
	void reset();
};

#endif
