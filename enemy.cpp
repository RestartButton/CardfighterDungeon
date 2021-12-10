#include "enemy.h"

Enemy* Enemy::sInstance = NULL;

Enemy* Enemy::Instance(SDL_Renderer* r)
{
    if(sInstance == NULL)
        sInstance = new Enemy(r);

    return sInstance;
}

void Enemy::Release()
{
    delete sInstance;
    sInstance = NULL;
}

Enemy::Enemy(SDL_Renderer* renderer)
{
    diamond = loadImage(renderer, "diamond.bmp");
    skeleton = loadImage(renderer, "skeleton.bmp");
    cyborg = loadImage(renderer, "cyborg.bmp");
    elf = loadImage(renderer, "elf.bmp");
    ciclops = loadImage(renderer, "ciclops.bmp");
    argonalta = loadImage(renderer, "argonalta.bmp");
}

void Enemy::setEnemy(int level)
{
    srand(time(NULL));
    type = (rand() % 6) + 1;
    eMaxLife = 6  + 6 * (level / 2);
    eLife = eMaxLife;
    if(type == 1){   ///diamond
        eDeck[0] = 1;
        eDeck[1] = 1;
        eDeck[2] = 2;
        eDeck[3] = 2;
        eDeck[4] = 2;
        ///cout << "diamond deck set" << endl;
    } else if (type == 2){   ///ciclops
        eDeck[0] = 1;
        eDeck[1] = 1;
        eDeck[2] = 1;
        eDeck[3] = 1;
        eDeck[4] = 1;
        ///cout << "ciclops deck set" << endl;
    } else if (type == 3){   ///skeleton
        eDeck[0] = 1;
        eDeck[1] = 1;
        eDeck[2] = 1;
        eDeck[3] = 2;
        eDeck[4] = 2;
        ///cout << "skeleton deck set" << endl;
    } else if (type == 4){   ///argonalta
        eDeck[0] = 1;
        eDeck[1] = 1;
        eDeck[2] = 1;
        eDeck[3] = 3;
        eDeck[4] = 3;
        ///cout << "argonalta deck set" << endl;
    } else if (type == 5){   ///cyborg
        eDeck[0] = 1;
        eDeck[1] = 1;
        eDeck[2] = 3;
        eDeck[3] = 3;
        eDeck[4] = 3;
        ///cout << "cyborg deck set" << endl;
    } else if (type == 6){   ///elf
        eDeck[0] = 3;
        eDeck[1] = 3;
        eDeck[2] = 3;
        eDeck[3] = 3;
        eDeck[4] = 3;
        ///cout << "elf deck set" << endl;
    }
    for(int i = 0; i < 5; i++)
        eCUR_deck[i] = eDeck[i];
}

void Enemy::DrawCard()
{
    int x;

    srand(time(NULL));

    do{
        x = rand() % 5;
    } while(eCUR_deck[x] == NULL);

    eCUR_card.type = eCUR_deck[x];
    eCUR_deck[x] = NULL;
    eCUR_card.effect = (rand() % 3) + 1;
}

bool Enemy::isDead()
{
    if(!sDead)
        return false;

    return true;
}

void Enemy::resetDeath()
{
    sDead = false;
}

void Enemy::damage()
{
    int x = rollDie();
    ///cout << "enemy damaged ( " << x << " )" << endl;
    eLife -= x;
}

bool Enemy::getShowCard()
{
    return showCard;
}

void Enemy::setShowCard(bool b)
{
    showCard = b;
}

float Enemy::getLife()
{
    return eLife;
}

float Enemy::getMaxLife()
{
    return eMaxLife;
}

void Enemy::Update()
{
    if(eLife <= 0){
        eLife = 0;
        sDead = true;
    }
}

void Enemy::Render(SDL_Renderer* r)
{
    src.x = 0;
    src.y = 0;
    dst = {200, 200, 400, 300};
    if (type == 1){
        src.w = 200;
        src.h = 150;
        SDL_RenderCopy(r, diamond, &src, &dst);
    }
    else if (type == 2){
        src.w = 300;
        src.h = 300;
        SDL_RenderCopy(r, ciclops, &src, &dst);
    }
    else if (type == 3){
        src.w = 180;
        src.h = 245;
        SDL_RenderCopy(r, skeleton, &src, &dst);
    }
    else if (type == 4){
        src.w = 300;
        src.h = 300;
        SDL_RenderCopy(r, argonalta, &src, &dst);
    }
    else if (type == 5){
        src.w = 300;
        src.h = 300;
        SDL_RenderCopy(r, cyborg, &src, &dst);
    }
    else if (type == 6){
        src.w = 300;
        src.h = 300;
        SDL_RenderCopy(r, elf, &src, &dst);
    }
}
