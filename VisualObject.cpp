#include "VisualObject.h"

VisualObject::VisualObject(VectorI pos, SDL_Surface* sprite) : pos(pos), sprite(sprite), width(0), height(0)
{
	width = sprite->w;
	height = sprite->h;
}

void VisualObject::draw(SDL_Surface* destination)
{
    if (sprite != NULL)
    {
        SDL_Rect offset;
        offset.x = pos.x; offset.y = pos.y;
        SDL_BlitSurface(sprite, NULL, destination, &offset);
    }
}

uint VisualObject::w()
{
    return width;
}

uint VisualObject::h()
{
    return height;
}
