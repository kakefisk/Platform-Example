#include "GameObject.h"

GameObject::GameObject(VectorI pos, SDL_Surface* sprite) : VisualObject(pos, sprite), vel(VectorF(0,0)), startPos(pos), prevPos(pos) {}

void GameObject::step()
{
    prevPos.x = pos.x;
    prevPos.y = pos.y;
    pos.x += vel.x;
    pos.y += vel.y;
}

bool GameObject::collision(GameObject& obj)
{
    return (pos.y + h() >= obj.pos.y && pos.y <= obj.pos.y + obj.h() && pos.x + w() >= obj.pos.x && pos.x <= obj.pos.x + obj.w());
}

void GameObject::reset()
{
	pos.x = startPos.x;
    pos.y = startPos.y;
	prevPos.x = pos.x;
    prevPos.y = pos.y;
}
