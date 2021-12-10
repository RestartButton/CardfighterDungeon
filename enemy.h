#ifndef ENEMY_H
#define ENEMY_H

#include "utils.h"

class Enemy
{
    public:
        Card eCUR_card;

        static Enemy* Instance(SDL_Renderer* r);
        static void Release();

        void setEnemy(int level);
        void DrawCard();
        void damage();
        void resetDeath();
        void setShowCard(bool b);
        bool getShowCard();
        bool isDead();
        float getLife();
        float getMaxLife();

        void Update();
        void Render(SDL_Renderer* r);

    private:
        static Enemy* sInstance;

        float eMaxLife = 6;
        float eLife = 6;
        int type = 1;
        int eDeck[5] = {1, 1, 1, 2, 3};
        int eCUR_deck[5] = {1, 1, 1, 2, 3};
        bool sDead = false;
        bool showCard = false;

        SDL_Rect src;
        SDL_Rect dst;

        SDL_Texture* diamond;
        SDL_Texture* skeleton;
        SDL_Texture* cyborg;
        SDL_Texture* elf;
        SDL_Texture* ciclops;
        SDL_Texture* argonalta;

        Enemy(SDL_Renderer* renderer);

};

#endif // ENEMY_H
