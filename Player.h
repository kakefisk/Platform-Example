#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "SDL.h"

class Player : public GameObject
{
    int speed;
    int jumpSpeed;

    public:
    bool onGround;

    Player(VectorI pos, SDL_Surface* sprite);
    bool key_pressed(SDLKey key);
    void step();
};

#endif
