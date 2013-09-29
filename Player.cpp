#include "Player.h"

Player::Player(int x, int y, const char* filename) : GameObject(x, y, filename) {}

bool Player::key_pressed(SDLKey key)
{
    Uint8 *keystates = SDL_GetKeyState(NULL);
    return (keystates[key]);
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

    if (key_pressed(SDLK_UP))
    {
        yVel = -1;
    }
    else if (key_pressed(SDLK_DOWN))
    {
        yVel = 1;
    }
    else
    {
        yVel = 0;
    }
    GameObject::step();
}
