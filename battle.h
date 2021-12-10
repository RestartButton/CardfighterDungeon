#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED

#include "player.h"
#include "enemy.h"

struct Battle {
    int winner = 0;
    bool newGame = true;
    bool newBattle = true;
    bool changeCard = false;
    bool endTurn = false;
    bool newTurn = true;
    bool acceptCard = false;
};

int cardBattle(Enemy* enemy, Player* player);

#endif // BATTLE_H_INCLUDED
