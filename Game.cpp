#include "Game.h"
#include "ResourceManager.h"

Game::Game(uint width, uint height, uint bpp, const char* title) : width(width), height(height), bpp(bpp), title(title), screen(NULL), level(20, 15)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE);
    SDL_WM_SetCaption(title, NULL);

    loadResources();
    level.loadLevel("res/level2.map");
}

Game::~Game()
{
    SDL_Quit();
}

void Game::step()
{
    bool isRunning = true;
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        level.step();

        SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
        level.draw(screen);

        SDL_Flip(screen);
        SDL_Delay(10);
    }
}

void Game::loadResources()
{
    ResourceManager::addSprite("sprWall", "res/wall.png");
    ResourceManager::addSprite("sprBall", "res/ball.png");
}
