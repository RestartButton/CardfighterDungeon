#include "battle.h"

int cardBattle(Enemy* enemy, Player* player)
{
    if(enemy->eCUR_card.type == player->CUR_card.type){  ///stalemate
        ///cout << enemy->eCUR_card.type << " vs " << player->CUR_card.type << " = 0" << endl;
        return 0;
    }else if(enemy->eCUR_card.type == 1 && player->CUR_card.type == 2){  ///blue beats red
        ///cout << enemy->eCUR_card.type << " vs " << player->CUR_card.type << " = 1" << endl;
        return 1;   ///player wins
    }else if(enemy->eCUR_card.type == 1 && player->CUR_card.type == 3){  ///red beats green
        ///cout << enemy->eCUR_card.type << " vs " << player->CUR_card.type << " = 2" << endl;
        return 2;  ///enemy wins
    }else if(enemy->eCUR_card.type == 2 && player->CUR_card.type == 1){  ///blue beats red
        ///cout << enemy->eCUR_card.type << " vs " << player->CUR_card.type << " = 2" << endl;
        return 2;  ///enemy wins
    }else if(enemy->eCUR_card.type == 2 && player->CUR_card.type == 3){  ///green beats blue
        ///cout << enemy->eCUR_card.type << " vs " << player->CUR_card.type << " = 1" << endl;
        return 1;  ///player wins
    }else if(enemy->eCUR_card.type == 3 && player->CUR_card.type == 1){  ///red beats green
        ///cout << enemy->eCUR_card.type << " vs " << player->CUR_card.type << " = 1" << endl;
        return 1;  ///player wins
    }else if(enemy->eCUR_card.type == 3 && player->CUR_card.type == 2){  ///green beats blue
        ///cout << enemy->eCUR_card.type << " vs " << player->CUR_card.type << " = 2" << endl;
        return 2;  ///enemy wins
    }
}
