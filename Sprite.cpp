#include "sprite.h"
#include "SDL_image.h"

Sprite::Sprite(std::string filename) : sprite(NULL), width(0), height(0)
{
    setSprite(filename);
}

Sprite::~Sprite()
{
    SDL_FreeSurface(sprite);
}

void Sprite::setSprite(SDL_Surface* sprite)
{
    SDL_FreeSurface(sprite);
    this->sprite = sprite;
    width = sprite->w;
    height = sprite->h;
}

void Sprite::setSprite(std::string filename)
{
    SDL_Surface* image = IMG_Load(filename.c_str());
    if (image != NULL)
    {
        SDL_Surface* optimizedImage = SDL_DisplayFormatAlpha(image);
        if (optimizedImage != NULL)
        {
            setSprite(optimizedImage);
            SDL_FreeSurface(optimizedImage);
        }
        SDL_FreeSurface(image);
    }
}

SDL_Surface* Sprite::getSprite()
{
    return sprite;
}

int Sprite::w()
{
    return width;
}

int Sprite::h()
{
    return height;
}
