#include "VisualObject.h"

VisualObject::VisualObject(int x, int y, SDL_Surface* sprite) : x(x), y(y), sprite(sprite), width(0), height(0)
{
	width = sprite->w;
	height = sprite->h;
}

void VisualObject::draw(SDL_Surface* destination)
{
    if (sprite != NULL)
    {
        SDL_Rect offset;
        offset.x = x; offset.y = y;
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
