#include "Game.h"
#include "SDL.h"

int main(int argc, char* args[])
{
    Game game = Game(320, 240, 32, "Platform Example");
    game.step();

    return 0;
}
