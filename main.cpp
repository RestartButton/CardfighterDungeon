#include "game.h"

int main( int argc, char * argv[] )
{
    Game* game = Game::Instance();

    game->Run();

    Game::Release();
    game = NULL;

    return 0;
}
