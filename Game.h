#ifndef GAME_H
#define GAME_H

#include "Level.h"
#include <string>

class Game
{
    uint width;
    uint height;
    uint bpp;
    std::string title;

    SDL_Surface* screen;
    SDL_Event event;

    Level level;

    public:
    Game(uint width, uint height, uint bpp, const char* filename);
    ~Game();

    void step();

    private:
    void loadResources();
};

#endif
