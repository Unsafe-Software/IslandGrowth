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
    this->camera_target = {0.0f, 0.0f};
}

Game::~Game() {
    CloseWindow();
    LOG(INFO) << "Window closed";
}

void Game::Update() {
    if (IsKeyPressed(KEY_F1))
        this->debug = !this->debug;

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

void Game::updateCamera() {
    static float min_speed = 100.0f;
	static float min_effect_length = 1.0f;
	static float fraction_speed = 1.0f;
	Vector2 v_offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
	this->camera.offset = v_offset;
	Vector2 diff = Vector2Subtract(this->camera_target, this->camera.target);
	float length = Vector2Length(diff);

	if (length > min_effect_length) {
		float speed = fmaxf(fraction_speed * length, min_speed);
		this->camera.target = Vector2Add(this->camera.target, Vector2Scale(diff, speed * GetFrameTime() / length));
	}
}

void Game::drawGame() {
    DrawTexturePro(tilemap, (Rectangle){0, 0, 16, 16}, (Rectangle){128, 128, 64, 64}, (Vector2){32, 32}, 0.0f, WHITE);
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
