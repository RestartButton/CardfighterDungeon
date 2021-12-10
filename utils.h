#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <time.h>
using namespace std;

struct Card {
    int type = 1; /// 1 = red, 2 = blue, 3 = green
    int effect = 0; /// default card effect: null
    SDL_Texture* image = NULL;
};

struct Button {
    int sprite = 0;
    int fx = 0;
    SDL_Rect bPosition;
    SDL_Texture* image;
};

struct UI {
    Button deck;
    SDL_Rect pLife = {5, 5, 359, 42};
    SDL_Rect eLife = {436, 5, 359, 42};
    SDL_Rect CUR_pLife = {5, 5, 359, 42};
    SDL_Rect CUR_eLife = {436, 5, 359, 42};
};

int rollDie();

SDL_Texture* loadImage( SDL_Renderer* renderer, const char* image );
Mix_Chunk* loadSFX(const char* path);
Mix_Music* loadBGM(const char* path);
#endif // UTILS_H_INCLUDED
