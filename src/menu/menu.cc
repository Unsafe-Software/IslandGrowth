#include "menu.hh"

namespace Engine {
    Menu::Menu(YAML::Node config) {
        this->config = config;
        LOG(INFO) << "Menu initialized";
    }

    Menu::~Menu() {
        LOG(INFO) << "Menu closed";
    }

    int Menu::Update() {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Menu", 190, 200, 20, BLACK);
        DrawText("Press Enter to start", 160, 220, 20, BLACK);
        EndDrawing();

        if (IsKeyDown(KEY_ENTER))
            return GAME;

        return MENU;
    }
}
