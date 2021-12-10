#include "game.h"

Game* Game::sInstance = NULL;
bool Game::sInitialized = false;

Game* Game::Instance()
{
    if(sInstance == NULL)
        sInstance = new Game();

    return sInstance;
}

void Game::Release()
{
    delete sInstance;
    sInstance = NULL;

    sInitialized = false;
}

bool Game::Initialized()
{
    return sInitialized;
}

Game::Game()
{
    isRunning = true;
    gamestate = "menu";

    sInitialized = Init();

    player = Player::Instance();
    enemy = Enemy::Instance(renderer);

    hurt = loadSFX("hurt.wav");
    lose = loadSFX("LoseSound.wav");

    battleMusic = loadBGM("music.wav");
    menuMusic = loadBGM("menuOST.wav");

    menu = loadImage(renderer, "menu.bmp");
    logo = loadImage(renderer, "logo.bmp");
    deckSelection = loadImage(renderer, "choose_your_deck.bmp");
    gameover = loadImage(renderer, "gameover.bmp");
    room = loadImage(renderer, "room.bmp");
    credits = loadImage(renderer, "credits.bmp");

    onceRed = loadImage(renderer, "red1.bmp");
    twiceRed = loadImage(renderer, "red2.bmp");
    thriceRed = loadImage(renderer, "red3.bmp");

    onceBlue = loadImage(renderer, "blue1.bmp");
    twiceBlue = loadImage(renderer, "blue2.bmp");
    thriceBlue = loadImage(renderer, "blue3.bmp");

    onceGreen = loadImage(renderer, "green1.bmp");
    twiceGreen = loadImage(renderer, "green2.bmp");
    thriceGreen = loadImage(renderer, "green3.bmp");

    ui.deck.image = loadImage(renderer, "deck.bmp");
    vs = loadImage(renderer, "vs.bmp");

    start.image = loadImage(renderer, "start.bmp");
    bCredits.image = loadImage(renderer, "b_Credits.bmp");
    exit.image = loadImage(renderer, "exit.bmp");

    firstDeck.image = loadImage(renderer, "1st_deck.bmp");
    secondDeck.image = loadImage(renderer, "2nd_deck.bmp");
    thirdDeck.image = loadImage(renderer, "3rd_deck.bmp");
    fourthDeck.image = loadImage(renderer, "4th_deck.bmp");
}

Game::~Game()
{
    Player::Release();
    player = NULL;

    Enemy::Release();
    enemy = NULL;

    Mix_FreeChunk(hurt);
    hurt = NULL;

    Mix_FreeChunk(lose);
    lose = NULL;

    Mix_FreeMusic(menuMusic);
    menuMusic = NULL;

    Mix_FreeMusic(battleMusic);
    battleMusic = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    Mix_Quit();
    SDL_Quit();
}

bool Game::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout << "SDL Initialization Error: " << SDL_GetError() << endl;
        return false;
    }

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0){
        cout << "Mixer Initialization Error: " << Mix_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow("Cardfighter Dungeon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    if(window == NULL){
        cout << "Window Creation Error: " << SDL_GetError() << endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL){
        cout << "Renderer Creation Error: " << SDL_GetError() << endl;
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Game::menuReset()
{
    enter = false;
    up = false;
    down = false;
    CUR_OPTION = 0;
}


void Game::Input()
{
    while ( SDL_PollEvent(&event)) {
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_BACKSPACE:
                    if(gamestate == "gameover")
                        gamestate = "menu";
                    else if(gamestate == "credits")
                        gamestate = "menu";
                    break;

                case SDLK_z:
                    if(gamestate == "battle"){
                        battle.acceptCard = true;
                    } else if(gamestate == "menu" || gamestate == "deckSelection"){
                        enter = true;
                    }
                    break;
                case SDLK_x:
                    if(gamestate == "battle"){
                        battle.changeCard = true;
                    }
                    break;

                case SDLK_UP:
                    if(gamestate == "menu" || gamestate == "deckSelection"){
                        up = true;
                    }
                    break;
                case SDLK_DOWN:
                    if(gamestate == "menu" || gamestate == "deckSelection"){
                        down = true;
                    }
                    break;
            }
        }
        if(event.type == SDL_QUIT)
        {
            isRunning = false;
        }
    }
}

void Game::Update()
{
    if(gamestate == "menu")
    {
        if(reset){
            reset = false;
            menuReset();
        }

        if(screenOptions[CUR_OPTION] == "start"){
            start.sprite = 1;
            bCredits.sprite = 0;
            exit.sprite = 0;
        }
        else if(screenOptions[CUR_OPTION] == "credits"){
            start.sprite = 0;
            bCredits.sprite = 1;
            exit.sprite = 0;
        }
        else if(screenOptions[CUR_OPTION] == "exit"){
            start.sprite = 0;
            bCredits.sprite = 0;
            exit.sprite = 1;
        }

        if(up){
            up = false;
            CUR_OPTION--;
            if(CUR_OPTION < 0)
                CUR_OPTION = 2;
        }
        if(down){
            down = false;
            CUR_OPTION++;
            if(CUR_OPTION > 2)
                CUR_OPTION = 0;
        }
        if(enter){
            enter = false;
            reset = true;
            if(screenOptions[CUR_OPTION] == "start")
                gamestate = "deckSelection";
            else if(screenOptions[CUR_OPTION] == "credits")
                gamestate = "credits";
            else if(screenOptions[CUR_OPTION] == "exit")
                isRunning = false;
        }

    }
    else if(gamestate == "deckSelection")
    {
        if(reset){
            reset = false;
            menuReset();
        }

        if(selectionOptions[CUR_OPTION] == "first"){
            firstDeck.sprite = 1;
            secondDeck.sprite = 0;
            thirdDeck.sprite = 0;
            fourthDeck.sprite = 0;
        } else if(selectionOptions[CUR_OPTION] == "second"){
            firstDeck.sprite = 0;
            secondDeck.sprite = 1;
            thirdDeck.sprite = 0;
            fourthDeck.sprite = 0;
        } else if(selectionOptions[CUR_OPTION] == "third"){
            firstDeck.sprite = 0;
            secondDeck.sprite = 0;
            thirdDeck.sprite = 1;
            fourthDeck.sprite = 0;
        } else if(selectionOptions[CUR_OPTION] == "fourth"){
            firstDeck.sprite = 0;
            secondDeck.sprite = 0;
            thirdDeck.sprite = 0;
            fourthDeck.sprite = 1;
        }

        if(up){
            up = false;
            CUR_OPTION--;
            if(CUR_OPTION < 0)
                CUR_OPTION = 3;
        }
        if(down){
            down = false;
            CUR_OPTION++;
            if(CUR_OPTION > 3)
                CUR_OPTION = 0;
        }

        if(enter){
            enter = false;
            reset = true;
            battle.newGame = true;
            battle.newBattle = true;
            battle.newTurn = true;
            STOP_MUSIC = true;
            if(selectionOptions[CUR_OPTION] == "first"){
                deck_choice = 1;
                gamestate = "battle";
            } else if(selectionOptions[CUR_OPTION] == "second"){
                deck_choice = 2;
                gamestate = "battle";
            } else if(selectionOptions[CUR_OPTION] == "third"){
                deck_choice = 3;
                gamestate = "battle";
            } else if(selectionOptions[CUR_OPTION] == "fourth"){
                deck_choice = 4;
                gamestate = "battle";
            }
        }

    }
    else if(gamestate == "battle")
    {
        if(enemy->isDead()){
            enemy->resetDeath();
            battle.newBattle = true;
            player->levelUp();
            player->resetLife();
        }
        if(battle.newGame){
            battle.newGame = false;
            pSound = true;
            player->deckSelect(deck_choice);
            player->resetLevel();
            player->resetLife();
        }
        if(battle.newBattle){
            battle.newBattle = false;
            enemy->setEnemy(player->getLevel());
        }
        if(battle.newTurn){
            battle.newTurn = false;
            player->shuffleDeck();
            player->drawCard();
            enemy->DrawCard();

            if(player->CUR_card.type == 1){
                if(player->CUR_card.effect == 1)
                    player->CUR_card.image = onceRed;
                if(player->CUR_card.effect == 2)
                    player->CUR_card.image = twiceRed;
                if(player->CUR_card.effect == 3)
                    player->CUR_card.image = thriceRed;
            } else if(player->CUR_card.type == 2){
                if(player->CUR_card.effect == 1)
                    player->CUR_card.image = onceBlue;
                if(player->CUR_card.effect == 2)
                    player->CUR_card.image = twiceBlue;
                if(player->CUR_card.effect == 3)
                    player->CUR_card.image = thriceBlue;
            } else if(player->CUR_card.type == 3){
                if(player->CUR_card.effect == 1)
                    player->CUR_card.image = onceGreen;
                if(player->CUR_card.effect == 2)
                    player->CUR_card.image = twiceGreen;
                if(player->CUR_card.effect == 3)
                    player->CUR_card.image = thriceGreen;
            }

            if(enemy->eCUR_card.type == 1){
                if(enemy->eCUR_card.effect == 1)
                    enemy->eCUR_card.image = onceRed;
                if(enemy->eCUR_card.effect == 2)
                    enemy->eCUR_card.image = twiceRed;
                if(enemy->eCUR_card.effect == 3)
                    enemy->eCUR_card.image = thriceRed;
            } else if(enemy->eCUR_card.type == 2){
                if(enemy->eCUR_card.effect == 1)
                    enemy->eCUR_card.image = onceBlue;
                if(enemy->eCUR_card.effect == 2)
                    enemy->eCUR_card.image = twiceBlue;
                if(enemy->eCUR_card.effect == 3)
                    enemy->eCUR_card.image = thriceBlue;
            } else if(enemy->eCUR_card.type == 3){
                if(enemy->eCUR_card.effect == 1)
                    enemy->eCUR_card.image = onceGreen;
                if(enemy->eCUR_card.effect == 2)
                    enemy->eCUR_card.image = twiceGreen;
                if(enemy->eCUR_card.effect == 3)
                    enemy->eCUR_card.image = thriceGreen;
            }
        }
        if(battle.changeCard){
            wFrame = true;
            if(changeOver){
                changeOver = false;
                wFrame = false;
                battle.changeCard = false;
                battle.endTurn = true;
                SDL_Delay(1000);
            }
            if(wFrame){
                changeOver = true;
                player->drawCard();
            }
        }
        else if(battle.acceptCard){
            battle.acceptCard = false;
            battle.endTurn = true;
        }
        if(battle.endTurn){
            battle.endTurn = false;
            battle.newTurn = true;
            enemy->setShowCard(true);
            battle.winner = 0;
            battle.winner = cardBattle(enemy, player);
            if(battle.winner == 1){
                for(int i = 0; i < player->CUR_card.effect; i++){
                    enemy->damage();
                }
            }
            else if(battle.winner == 2){
                for(int i = 0; i < enemy->eCUR_card.effect; i++){
                    player->damage();
                    Mix_PlayChannel(-1, hurt, 0);
                }
            } else if(battle.winner == 0){
                ///nothing
            }
        }
        player->checkDeck();
        if(player->getLife() <= 0){
            player->setLife(0);
            STOP_MUSIC = true;
            gamestate = "gameover";
            pSound = true;
        }
        enemy->Update();
        ui.deck.sprite = (player->remaining() - 1);
    }
    else if (gamestate == "gameover")
    {
        if(pSound){
            Mix_PlayChannel(-1, lose, 0);
            pSound = false;
        }
    }
}

void Game::Sound()
{
    if(STOP_MUSIC){
        Mix_HaltMusic();
        STOP_MUSIC = false;
    }
    if(pSound){
        if(gamestate == "menu" || gamestate == "credits" || gamestate == "deckSelection"){
            Mix_PlayMusic(menuMusic, -1);
            pSound = false;
        }
        else if(gamestate == "battle"){
            Mix_PlayMusic(battleMusic, -1);
            pSound = false;
        }
    }
}

void Game::Render()
{
    SDL_RenderClear(renderer);

    if(gamestate == "menu"){

        SDL_RenderCopy(renderer, menu, NULL, NULL);
        src = {0, 0, 476, 349};
        dst = {112, 98, 576, 423};
        SDL_RenderCopy(renderer, logo, &src, &dst);
        src = {0, start.sprite * 72, 167, 72};
        dst = {0, 243, 167, 72};
        SDL_RenderCopy(renderer, start.image, &src, &dst);
        src = {0, bCredits.sprite * 72, 167, 72};
        dst = {0, 320, 167, 72};
        SDL_RenderCopy(renderer, bCredits.image, &src, &dst);
        src = {0, exit.sprite * 72, 167, 72};
        dst = {0, 397, 167, 72};
        SDL_RenderCopy(renderer, exit.image, &src, &dst);
    } else if(gamestate == "credits"){

        SDL_RenderCopy(renderer, credits, NULL, NULL);
    } else if(gamestate == "deckSelection"){

        SDL_RenderCopy(renderer, deckSelection, NULL, NULL);
        src = {0, firstDeck.sprite * 50, 176, 50};
        dst = {212, 119, 352, 100};
        SDL_RenderCopy(renderer, firstDeck.image, &src, &dst);
        src = {0, secondDeck.sprite * 50, 176, 50};
        dst = {212, 229, 352, 100};
        SDL_RenderCopy(renderer, secondDeck.image, &src, &dst);
        src = {0, thirdDeck.sprite * 50, 176, 50};
        dst = {212, 339, 352, 100};
        SDL_RenderCopy(renderer, thirdDeck.image, &src, &dst);
        src = {0, fourthDeck.sprite * 50, 176, 50};
        dst = {212, 449, 352, 100};
        SDL_RenderCopy(renderer, fourthDeck.image, &src, &dst);
    } else if(gamestate == "battle"){

        SDL_RenderCopy(renderer, room, NULL, NULL);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderFillRect(renderer, &ui.pLife);
        SDL_RenderFillRect(renderer, &ui.eLife);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        ui.CUR_pLife.w = (player->getLife() / player->getMaxLife()) * 359;
        ui.CUR_eLife.w = (enemy->getLife() / enemy->getMaxLife()) * 359;
        SDL_RenderFillRect(renderer, &ui.CUR_pLife);
        SDL_RenderFillRect(renderer, &ui.CUR_eLife);
        dst = {351, 5, 98, 81};
        SDL_RenderCopy(renderer, vs, NULL, &dst);
        enemy->Render(renderer);
        if(enemy->getShowCard()){
            if(frameOver){
                frameOver = false;
                enemy->setShowCard(false);
                SDL_Delay(1000);
            }
            src = {0, 0, 117, 147};
            dst = {340, 163, 117, 147};
            SDL_RenderCopyEx(renderer, enemy->eCUR_card.image, &src, &dst, 180.0, NULL, SDL_FLIP_NONE);
            frameOver = true;
        }
        src = {0, ui.deck.sprite * 127, 218, 127};
        dst = {577, 468, 218, 127};
        SDL_RenderCopy(renderer, ui.deck.image, &src, &dst);
        src = {0, 0, 117, 147};
        dst = {313, 373, 175, 220};
        SDL_RenderCopy(renderer, player->CUR_card.image, &src, &dst);
    } else if(gamestate == "gameover"){
        SDL_RenderCopy(renderer, gameover, NULL, NULL);
    }

    SDL_RenderPresent(renderer);
}

void Game::Run()
{
    while(isRunning){
        ///cout << gamestate << endl;
        Input();
        Update();
        Sound();
        Render();
        SDL_Delay(1000 / FRAME_RATE);
    }
}
