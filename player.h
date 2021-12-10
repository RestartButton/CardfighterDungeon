#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"

class Player
{
    public:
        static Player* Instance();
        static void Release();

        Card CUR_card;

        void deckSelect(int deck_choice);
        void shuffleDeck();
        void drawCard();
        void levelUp();
        void resetLevel();
        void resetLife();
        void damage();
        void checkDeck();
        void setLife(int x);
        int getLevel();
        int remaining();
        float getLife();
        float getMaxLife();

        Player();

    private:
        static Player* sInstance;

        int level = 1;
        float maxLife = 20;
        float life = 20;
        int deck[5] = {1, 1, 1, 2, 3};  ///1 = red, 2 = blue, 3 = green
        int CUR_deck[5] = {1, 1, 1, 2, 3};
        int remainingCard;
};

#endif // PLAYER_H
