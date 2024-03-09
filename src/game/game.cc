#include "game.hh"

namespace Engine {
    Game::Game(YAML::Node config) : player(nullptr) {
        this->config = config;

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

        this->player = Player(this->current_world);
    }

    Game::~Game() {
        LOG(INFO) << "Game closed";
    }

    int Game::Update() {
        if (IsKeyPressed(KEY_F1))
            this->debug = !this->debug;
        if (IsKeyPressed(KEY_F2))
            this->player.noClip = !this->player.noClip;
        if (IsKeyDown(KEY_W))
            this->player.velocity.y -= this->speed * GetFrameTime();
        if (IsKeyDown(KEY_S))
            this->player.velocity.y += this->speed * GetFrameTime();
        if (IsKeyDown(KEY_A))
            this->player.velocity.x -= this->speed * GetFrameTime();
        if (IsKeyDown(KEY_D))
            this->player.velocity.x += this->speed * GetFrameTime();
        this->camera_target = {this->player.bounds.x, this->player.bounds.y};

        BeginDrawing();
        this->updateCamera();
        BeginMode2D(this->camera);
        ClearBackground(WHITE);
        this->drawGame();
        player.Update(this->debug);
        player.Draw();
        EndMode2D();
        this->drawUI();
        EndDrawing();

        return GAME;
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
                "Camera pos: " + std::to_string(this->camera.target.x) +
                "px x " + std::to_string(this->camera.target.x) + "px y"
            ).c_str(),
            3, 42, 20, GRAY
        );
        DrawText((
                "Player pos: " + std::to_string(this->player.bounds.x) +
                "x " + std::to_string(this->player.bounds.y) + "y"
            ).c_str(),
            3, 62, 20, GRAY
        );
        DrawText((
                "Player noclip (F2): " + std::string(this->player.noClip ? "true" : "false")
            ).c_str(),
            3, 82, 20, GRAY
        );
    }
}
