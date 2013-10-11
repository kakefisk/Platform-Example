#include "ResourceManager.h"
#include "SDL.h"
#include "SDL_image.h"

#include <string>

std::unordered_map<std::string, SDL_Surface*> ResourceManager::sprites;

SDL_Surface* ResourceManager::getSprite(std::string key)
{
    return sprites.at(key);
}

void ResourceManager::addSprite(std::string key, std::string filename)
{
	sprites.insert(std::make_pair(key, loadSprite(filename)));
}

SDL_Surface* ResourceManager::loadSprite(std::string filename)
{
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = IMG_Load(filename.c_str());

	if (loadedSurface != NULL)
	{
		optimizedSurface = SDL_DisplayFormat(loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}
