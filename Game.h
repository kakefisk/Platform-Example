#ifndef GAME_H
#define GAME_H

#include <string>
#include "Level.h"

class Game
{
    int width;
    int height;
    int bpp;
    std::string title;

    SDL_Surface* screen;
    SDL_Event event;

    Level level;

    public:
    Game(int, int, int, const char*);
    ~Game();

    void step();

    private:
    void apply_surface(int, int, SDL_Surface*, SDL_Surface*);
};

#endif
