#include "init.c"
#include "game/game.hh"

#include "entity/entity.hh"
#include "entity/mob.hh"

#define PLAYER_SPEED 250.0f

int main() {
    Engine::Game* game = new Engine::Game(init());
    while (!game->ShouldClose())
        game->Update();
    delete game;
    return 0;
}
