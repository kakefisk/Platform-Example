#include "level.h"
#include <cmath>

Level::Level(int width, int height) : width(width), height(height) {}

void Level::loadLevel(int data[])
{
    for (int i = 0; i < sizeof(data)/sizeof(int); i++)
    {
        int x = i % width;
        int y = floor(i/y);
        if (data[i] == 1)
        {
            instances.push_back(GameObject(x, y, "res/wall.png"));
        }
    }
}

void Level::step()
{

}

void Level::draw(SDL_Surface* destination)
{
    for (int i = 0; i < instances.size(); i++)
    {
        instances[i].draw(destination);
    }
}
