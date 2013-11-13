#include "GameObject.h"

GameObject::GameObject(Vector pos, SDL_Surface* sprite) : VisualObject(pos, sprite), vel(Vector(0,0)), startPos(pos), prevPos(pos) {}

void GameObject::step()
{
    prevPos = pos;
    pos += vel;
}

bool GameObject::collision(GameObject& obj)
{
    return (pos.y + h() >= obj.pos.y && pos.y <= obj.pos.y + obj.h() && pos.x + w() >= obj.pos.x && pos.x <= obj.pos.x + obj.w());
}

void GameObject::reset()
{
	pos = startPos;
	prevPos = pos;
}