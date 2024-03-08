#include "init.c"
#include "game/game.hh"

int main() {
    Engine::Game* game = new Engine::Game(init());
    while (!game->ShouldClose())
        game->Update();
    delete game;
    return 0;
}
