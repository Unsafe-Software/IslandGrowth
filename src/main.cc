#include "init.c"
#include "game/game.hh"

#include "entity/entity.hh"

int main() {
    Engine::Entity* entity = new Engine::Entity();
    delete entity;

    // Engine::Game* game = new Engine::Game(init());
    // while (!game->ShouldClose())
    //     game->Update();
    // delete game;
    return 0;
}
