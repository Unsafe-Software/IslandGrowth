#include "init.c"
#include "game/game.hh"

int main() {
    Game* game = new Game(init());
    while (!game->ShouldClose())
        game->Update();
    delete game;
    return 0;
}
