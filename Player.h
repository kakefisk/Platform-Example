#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "GameObject.h"

class Player : public GameObject
{
    public:
    bool key_pressed(SDLKey);
    void step();
};

#endif
