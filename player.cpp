#include "player.h"

Player* Player::sInstance = NULL;

Player* Player::Instance()
{
    if(sInstance == NULL)
        sInstance = new Player();

    return sInstance;
}

void Player::Release()
{
    delete sInstance;
    sInstance = NULL;
}

Player::Player()
{

}

void Player::deckSelect(int deck_choice)
{
    if(deck_choice == 1){
        deck[0] = 1;
        deck[1] = 1;
        deck[2] = 1;
        deck[3] = 2;
        deck[4] = 3;
    }else if(deck_choice == 2){
        deck[0] = 1;
        deck[1] = 2;
        deck[2] = 2;
        deck[3] = 2;
        deck[4] = 3;
    }else if(deck_choice == 3){
        deck[0] = 1;
        deck[1] = 2;
        deck[2] = 3;
        deck[3] = 3;
        deck[4] = 3;
    }else if(deck_choice == 4){
        deck[0] = 1;
        deck[1] = 1;
        deck[2] = 2;
        deck[3] = 2;
        deck[4] = 3;
    }
    for(int i = 0; i < 5; i++)
        CUR_deck[i] = deck[i];
}

void Player::shuffleDeck()
{
    int temp_Card;
    int x;

    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        do{
            x = rand() % 5;
        } while(CUR_deck[x] == NULL);

        if(CUR_deck[i] != NULL){
            temp_Card = CUR_deck[i];
            CUR_deck[i] = CUR_deck[x];
            CUR_deck[x] = temp_Card;
        }
    }
}

void Player::drawCard()
{
    int x;

    srand(time(NULL));

    do{
        x = rand() % 5;
    } while(CUR_deck[x] == NULL);

    CUR_card.type = CUR_deck[x];
    CUR_deck[x] = NULL;
    CUR_card.effect = (rand() % 3) + 1;
}

void Player::levelUp()
{
    level++;
}

void Player::resetLevel()
{
    level = 1;
}

void Player::resetLife()
{
    life = maxLife;
}

int Player::getLevel()
{
    return level;
}

int Player::remaining()
{
    return remainingCard;
}

float Player::getLife()
{
    return life;
}

float Player::getMaxLife()
{
    return maxLife;
}

void Player::damage()
{
    int x = rollDie();
    ///cout << "player damaged( " << x << ")" << endl;
    life -= x;
}

void Player::setLife(int x)
{
    life = x;
}

void Player::checkDeck()
{
    remainingCard = 5;
    for(int i = 0; i < 5; i++){
        if(CUR_deck[i] == NULL)
            remainingCard--;
    }

    if(remainingCard <= 0){
        for(int i = 0; i < 5; i++){
            CUR_deck[i] = deck[i];
        }
    }
    //cout << remainingCard << endl;
}
