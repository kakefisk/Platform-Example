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

    Player(int x, int y, SDL_Surface* sprite);
    bool key_pressed(SDLKey key);
    void step();
    bool collision_hor(int x, int y, int &offsetx);
    bool collision_ver(int x, int y, int &offsety);
};

#endif
