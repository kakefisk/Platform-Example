#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "SDL.h"
#include <unordered_map>
#include <string>

class ResourceManager
{
    static std::unordered_map<std::string, SDL_Surface*> sprites;

    public:
    static SDL_Surface* getSprite(std::string key);
    static void addSprite(std::string key, std::string);

    private:
    static SDL_Surface* loadSprite(std::string filename);
};

#endif
