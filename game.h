#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "utils.h"
#include "battle.h"
using namespace std;

class Game
{
    public:
        static Game* Instance();
        static void Release();


        void Run();

    private:
        static Game* sInstance;
        static bool sInitialized;

        const int FRAME_RATE = 16;

        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event event;
        SDL_Rect src;
        SDL_Rect dst;

        char* gamestate;
        int deck_choice = 1;
        bool isRunning;
        bool changeOver = false;
        bool frameOver = false;
        bool wFrame = false;
        bool STOP_MUSIC = false;
        bool pSound = true;

        ///menu
        int CUR_OPTION;
        bool up, down, enter;
        bool reset = true;

        ///start screen
        string screenOptions[3]  = {"start", "credits", "exit"};

        ///deck selection
        string selectionOptions[4] = {"first", "second", "third", "fourth"};

        ///musics
        Mix_Music* menuMusic;
        Mix_Music* battleMusic;

        ///sfx
        Mix_Chunk* hurt;
        Mix_Chunk* lose;

        ///entities
        Battle battle;
        Player* player;
        Enemy* enemy;

        ///hud
        UI ui;
        SDL_Texture* vs;

        ///states
        SDL_Texture* menu;
        SDL_Texture* logo;
        SDL_Texture* deckSelection;
        SDL_Texture* credits;
        SDL_Texture* room;
        SDL_Texture* gameover;

        ///buttons
        Button start;
        Button bCredits;
        Button exit;
        Button firstDeck;
        Button secondDeck;
        Button thirdDeck;
        Button fourthDeck;

        ///cards
        SDL_Texture* onceRed;
        SDL_Texture* twiceRed;
        SDL_Texture* thriceRed;

        SDL_Texture* onceBlue;
        SDL_Texture* twiceBlue;
        SDL_Texture* thriceBlue;

        SDL_Texture* onceGreen;
        SDL_Texture* twiceGreen;
        SDL_Texture* thriceGreen;

        static bool Initialized();

        ///main methods
        void Sound();
        void Input();
        void Update();
        void Render();
        bool Init();

        ///start sreen
        void menuReset();

        Game();
        virtual ~Game();
};

#endif // GAME_H
