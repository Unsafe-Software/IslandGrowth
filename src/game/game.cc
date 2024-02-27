#include "game.hh"

namespace Engine {
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

        this->tilemap = new Engine::Graphics::Tilemap("data/tilemaps/tiles.json");

        this->debug = this->config["debug"] ? this->config["debug"].as<bool>() : false;
        this->targetFPS = this->config["window"]["fps"] ? this->config["window"]["fps"].as<int>() : 30;
        this->camera_target = {0.0f, 0.0f};

        this->current_world = new World("data/worlds/debug.json");
        this->speed = this->config["gameplay"]["speed"] ? this->config["gameplay"]["speed"].as<float>() : 1.0f;
    }

    Game::~Game() {
        CloseWindow();
        LOG(INFO) << "Window closed";
    }

    void Game::Update() {
        if (IsKeyPressed(KEY_F1))
            this->debug = !this->debug;
        if (IsKeyDown(KEY_W))
            this->camera_target.y -= this->speed * GetFrameTime();
        if (IsKeyDown(KEY_S))
            this->camera_target.y += this->speed * GetFrameTime();
        if (IsKeyDown(KEY_A))
            this->camera_target.x -= this->speed * GetFrameTime();
        if (IsKeyDown(KEY_D))
            this->camera_target.x += this->speed * GetFrameTime();

        BeginDrawing();
        this->updateCamera();
        BeginMode2D(this->camera);
        ClearBackground(WHITE);
        this->drawGame();
        EndMode2D();
        this->drawUI();
        EndDrawing();
    }

    bool Game::ShouldClose() {
        return WindowShouldClose();
    }

    void Game::drawGame() {
        for (int x = 0; x < this->current_world->GetWidth(); x++) {
            for (int y = 0; y < this->current_world->GetHeight(); y++) {
                DrawTexturePro(
                    this->tilemap->GetTexture(),
                    this->tilemap->GetTile(this->current_world->GetTile(x, y)),
                    (Rectangle){x * 16.0f, y * 16.0f, 16.0f, 16.0f},
                    (Vector2){0, 0}, 0.0f, WHITE
                );
            }
        }

        DrawRectangleLinesEx(
            (Rectangle){
                this->camera_target.x * 16.0f - 8.0f,
                this->camera_target.y * 16.0f - 8.0f,
                16.0f, 16.0f
            }, 1, RED
        );
    }

    void Game::updateCamera() {
        static float min_speed = 10.0f;
        static float min_effect_length = 2.5f;
        static float fraction_speed = 3.0f;
        Vector2 v_offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
        this->camera.offset = v_offset;
        Vector2 diff = Vector2Subtract(
            Vector2Multiply(
                this->camera_target,
                {16.0f, 16.0f}
            ),
            this->camera.target
        );
        float length = Vector2Length(diff);

        if (length > min_effect_length) {
            float speed = fmaxf(fraction_speed * length, min_speed);
            this->camera.target = Vector2Add(this->camera.target, Vector2Scale(diff, speed * GetFrameTime() / length));
        }
    }

    void Game::drawUI() {
        this->drawDebug();
    }

    void Game::drawDebug() {
        if (!this->debug)
            return;

        DrawText("Debug mode (F1)", 3, 2, 20, GRAY);
        DrawText((
                "FPS: " + std::to_string(GetFPS()) +
                "/" + std::to_string(this->targetFPS)
            ).c_str(),
            3, 22, 20, GRAY
        );
        DrawText((
                "Camera target: " + std::to_string(this->camera_target.x) +
                "x " + std::to_string(this->camera_target.y) + "y"
            ).c_str(),
            3, 42, 20, GRAY
        );
        DrawText((
                "Camera pos: " + std::to_string(this->camera.target.x) +
                "x " + std::to_string(this->camera.target.x) + "y"
            ).c_str(),
            3, 62, 20, GRAY
        );
    }
}
