#include "Player.h"

Player::Player(Vector pos, SDL_Surface* sprite) : GameObject(pos, sprite), speed(2) {onGround = false;}

bool Player::key_pressed(SDLKey key)
{
    const Uint8 *keystates = SDL_GetKeyState(NULL);
    return keystates[key];
}

void Player::step()
{
    if (key_pressed(SDLK_LEFT))
    {
        vel.x = -1;
    }
    else if (key_pressed(SDLK_RIGHT))
    {
        vel.y = 1;
    }
    else
    {
        vel.x = 0;
    }

    if (key_pressed(SDLK_SPACE) && onGround)
    {
        vel.y = -5;
        onGround = false;
    }

    if (!onGround)
    {
        vel.y += 0.2;
		if (vel.y > 5)
		{
			vel.y = 5;
		}
    }

    GameObject::step();
}