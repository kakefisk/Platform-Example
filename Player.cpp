#include "Player.h"

Player::Player(int x, int y, SDL_Surface* sprite) : GameObject(x, y, sprite) {}

bool Player::key_pressed(SDLKey key)
{
    const Uint8 *keystates = SDL_GetKeyState(NULL);
    return keystates[key];
}

void Player::step()
{
    if (key_pressed(SDLK_LEFT))
    {
        xVel = -1;
    }
    else if (key_pressed(SDLK_RIGHT))
    {
        xVel = 1;
    }
    else
    {
        xVel = 0;
    }

    if (key_pressed(SDLK_SPACE) && onGround)
    {
        yVel = -4;
        onGround = false;
    }

    if (!onGround)
    {
        yVel += 0.2;
		if (yVel > 4)
		{
			yVel = 4;
		}
    }

    GameObject::step();
}