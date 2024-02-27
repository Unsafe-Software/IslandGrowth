#include "game.hh"

Game::Game(YAML::Node config) {
    this->config = config;

    InitWindow(
        (this->config["window"]["window"] ? this->config["window"]["width"].as<int>() : 1280),
        (this->config["window"]["window"] ? this->config["window"]["height"].as<int>() : 720),
        (this->config["window"]["window"] ? this->config["window"]["title"].as<std::string>().c_str() : "Island Growth")
    );
    SetTargetFPS(
        (this->config["window"]["fps"] ? this->config["window"]["fps"].as<int>() : 30)
    );
    LOG(INFO) << "Window initialized";

    this->camera = {};
    this->camera.target = {0.0f, 0.0f};
    this->camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    this->camera.rotation = 0.0f;
    this->camera.zoom = this->config["window"]["zoom"] ? this->config["window"]["zoom"].as<float>() : 1.0f;
    LOG(INFO) << "Camera initialized";

    this->tilemap = LoadTexture("assets/tilemap.png");
    LOG(INFO) << "Tilemap loaded";

    this->debug = this->config["debug"] ? this->config["debug"].as<bool>() : false;
    this->targetFPS = this->config["window"]["fps"] ? this->config["window"]["fps"].as<int>() : 30;
}

Game::~Game() {
    CloseWindow();
    LOG(INFO) << "Window closed";
}

void Game::Update() {
    if (IsKeyPressed(KEY_F1))
        this->debug = !this->debug;

    BeginDrawing();
    // BeginMode2D(camera);
    ClearBackground(WHITE);

    DrawTexturePro(tilemap, (Rectangle){0, 0, 16, 16}, (Rectangle){128, 128, 64, 64}, (Vector2){32, 32}, 0.0f, WHITE);

    // EndMode2D();
    // UI
    if (this->debug) {
        DrawText("Debug mode (F1)", 3, 2, 20, GRAY);
        DrawText((
                "FPS: " + std::to_string(GetFPS()) +
                "/" + std::to_string(this->targetFPS)
            ).c_str(),
            3, 22, 20, GRAY
        );
    }
    EndDrawing();
}

bool Game::ShouldClose() {
    return WindowShouldClose();
}
