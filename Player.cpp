#include "Player.h"

bool Player::key_pressed(SDLKey key)
{
    Uint8 *keystates = SDL_GetKeyState(NULL);
    return (keystates[key]);
}

void Player::step()
{
    if (key_pressed(SDLK_LEFT))
    {
        xVel = -4;
    }
    if (key_pressed(SDLK_UP))
    {
        yVel = -4;
    }
    if (key_pressed(SDLK_RIGHT))
    {
        xVel = 4;
    }
    if (key_pressed(SDLK_DOWN))
    {
        yVel = 4;
    }
}
