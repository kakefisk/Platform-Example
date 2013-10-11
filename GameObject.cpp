#include "GameObject.h"

GameObject::GameObject(int x, int y, SDL_Surface* sprite) : VisualObject(x, y, sprite), xVel(0), yVel(0), xStart(x), yStart(y), xPrev(x), yPrev(y) {}

void GameObject::step()
{
    xPrev = x;
    yPrev = y;

    x += xVel;
    y += yVel;
}

bool GameObject::collision(GameObject& obj)
{
    return (y + h() >= obj.y && y <= obj.y + obj.h() && x + w() >= obj.x && x <= obj.x + obj.w());
}

void GameObject::reset()
{
	x = xStart;
	y = yStart;
	xPrev = x;
	yPrev = y;
}