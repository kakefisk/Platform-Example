#include "Level.h"
#include "Player.h"
#include "ResourceManager.h"

#include <cmath>
#include <string>

Level::Level(uint width, uint height) : width(width), height(height) {}

void Level::loadLevel(std::vector<int> data)
{
    for (uint i = 0; i < data.size(); i++)
    {
        int x = (i % width)*16;
        int y = floor(i/width)*16;
        if (data[i] == 1)
        {
            instances.push_back(new GameObject(x, y, ResourceManager::getSprite(std::string("sprWall"))));
        }
        else if (data[i] == 2)
        {
            instances.push_back(new Player(x, y, ResourceManager::getSprite(std::string("sprBall"))));
        }
    }
}

void Level::step()
{
    for (uint i = 0; i < instances.size(); i++)
    {
        instances[i]->step();
    }
}

void Level::draw(SDL_Surface* destination)
{
    for (uint i = 0; i < instances.size(); i++)
    {
        instances[i]->draw(destination);
    }
}
