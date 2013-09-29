#include "GameObject.h"

GameObject::GameObject(int x, int y, SDL_Surface* sprite) : x(x), y(y), xVel(0), yVel(0), sprite(sprite), width(0), height(0), xStart(x), yStart(y), xPrev(x), yPrev(y) {}

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
    SDL_BlitSurface(sprite, NULL, destination, &offset);
}

bool GameObject::collision(GameObject& obj)
{
    return (y + h() >= obj.y && y <= obj.y + obj.h() && x + w() >= obj.x && x <= obj.x + obj.w());
}

unsigned int GameObject::w()
{
    return width;
}

unsigned int GameObject::h()
{
    return height;
}
