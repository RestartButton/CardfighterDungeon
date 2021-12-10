#include "utils.h"

SDL_Texture* loadImage( SDL_Renderer* renderer, const char* image )
{
    SDL_Texture* img = NULL;

    SDL_Surface* surface = SDL_LoadBMP(image);
    if(surface == NULL){
        cout << "Image Load Error! Path: " << image << " Error: " << SDL_GetError() << endl;
        return img;
    }

    img = SDL_CreateTextureFromSurface(renderer, surface);
    if(img == NULL){
        cout << "Create Texture Error: " << SDL_GetError() << endl;
        return img;
    }

    SDL_FreeSurface(surface);

    return img;
}

Mix_Chunk* loadSFX(const char* path)
{
    Mix_Chunk* sound = Mix_LoadWAV(path);
    if(sound == NULL)
        cout << "Sound FX Load Error! Path: " << path << " Error: " << Mix_GetError() << endl;

    return sound;
}

Mix_Music* loadBGM(const char* path)
{
    Mix_Music* mus = Mix_LoadMUS(path);
    if(mus == NULL)
        cout << "Music Load Error! Path: " << path << " Error: " << Mix_GetError() << endl;

    return mus;
}

int rollDie()
{
    srand(time(NULL));

    return (rand() % 6) + 1;
}
