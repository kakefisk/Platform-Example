#include "level.h"
#include <cmath>
#include "Player.h"

Level::Level(int width, int height) : width(width), height(height) {}

void Level::loadLevel(std::vector<int> data)
{
    for (int i = 0; i < data.size(); i++)
    {
        int x = (i % width)*16;
        int y = floor(i/width)*16;
        if (data[i] == 1)
        {
            instances.push_back(GameObject(x, y, "res/wall.png"));
        }
        else if (data[i] == 2)
        {
            instances.push_back(Player(x, y, "res/ball.png"));
        }
    }
}

void Level::step()
{
    for (int i = 0; i < instances.size(); i++)
    {
        instances[i].step();
    }
}

void Level::draw(SDL_Surface* destination)
{
    for (int i = 0; i < instances.size(); i++)
    {
        instances[i].draw(destination);
    }
}
