#include "init.c"
#include "game/game.hh"
#include "world/world.hh"

#include <iostream>

int main() {
    World* world = new World("data/worlds/debug.json");
    world->Check();
    std::cout << world->GetTile(0, 0) << std::endl;
    delete world;

    // Game* game = new Game(init());
    // while (!game->ShouldClose())
    //     game->Update();
    // delete game;
    return 0;
}
