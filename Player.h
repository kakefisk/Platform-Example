#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "GameObject.h"

class Player : public GameObject
{
    public:
    Player(int, int, const char*);
    bool key_pressed(SDLKey);
    void step();
};

#endif
