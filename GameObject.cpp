#include "GameObject.h"

GameObject::GameObject(int x, int y, const char* filename) : x(x), y(y), xVel(0), yVel(0), sprite(filename), xStart(x), yStart(y), xPrev(x), yPrev(y) {}

void GameObject::step()
{
    xPrev = x;
    yPrev = y;

    x += xVel;
    y += yVel;
}

void GameObject::draw(SDL_Surface* destination)
{
    SDL_Rect offset;
    offset.x = x; offset.y = y;
    SDL_BlitSurface(sprite.getSprite(), NULL, destination, &offset);
}

bool GameObject::collision(GameObject obj)
{
    return (y + sprite.h() >= obj.y && y <= obj.y + obj.sprite.h() && x + sprite.w() >= obj.x && x <= obj.x + obj.sprite.w());
}
