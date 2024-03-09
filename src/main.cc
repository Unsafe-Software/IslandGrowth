#include <yaml-cpp/yaml.h>

#include "init.c"
#include "game/game.hh"
#include "menu/menu.hh"
#include "scenes.hh"

int main() {
    YAML::Node config = init();
    LOG(INFO) << "Initialing game scenes...";
    Engine::Game* game = new Engine::Game(config);
    Engine::Menu* menu = new Engine::Menu(config);
    LOG(INFO) << "Game scenes initialized";

    int scene = MENU;
    while (!game->ShouldClose()) {
        switch (scene) {
            case MENU:
                scene = menu->Update();
                break;
            case GAME:
                scene = game->Update();
                break;
            case END:
                break;
        }
    }

    delete game;
    CloseWindow();
    LOG(INFO) << "Window closed";
    return 0;
}
