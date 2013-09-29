#include "sprite.h"
#include "SDL_image.h"

Sprite::Sprite(const char* filename) : sprite(NULL), width(0), height(0)
{
    setSprite(filename);
}

void Sprite::free()
{
    SDL_FreeSurface(sprite);
}

void Sprite::setSprite(SDL_Surface* sprite)
{
    SDL_FreeSurface(this->sprite);
    this->sprite = sprite;
    width = sprite->w;
    height = sprite->h;
}

void Sprite::setSprite(const char* filename)
{
    SDL_Surface* image = IMG_Load(filename);
    if (image != NULL)
    {
        SDL_Surface* optimizedImage = SDL_DisplayFormatAlpha(image);
        if (optimizedImage != NULL)
        {
            setSprite(optimizedImage);
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
