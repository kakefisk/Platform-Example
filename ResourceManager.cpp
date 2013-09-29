#include "ResourceManager.h"
#include "SDL.h"
#include "SDL_image.h"

#include <string>

std::unordered_map<std::string, SDL_Surface*> ResourceManager::sprites;

SDL_Surface* ResourceManager::getSprite(std::string key)
{
    return sprites[key];
}

void ResourceManager::addSprite(std::string key, std::string filename)
{
    sprites.insert({key, loadSprite(filename)});
}

SDL_Surface* ResourceManager::loadSprite(std::string filename)
{
    SDL_Surface* optimizedImage = NULL;
    SDL_Surface* image = IMG_Load(filename.c_str());
    if (image != NULL)
    {
        optimizedImage = SDL_DisplayFormatAlpha(image);
        if (optimizedImage != NULL) {}
        SDL_FreeSurface(image);
    }
    return optimizedImage;
}
