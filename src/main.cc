#include "init.c"
#include "game/game.hh"

#include "entity/entity.hh"
#include "entity/mob.hh"

#include <raylib.h>

Vector2 calculateNewPlayerPos(const Rectangle player, const Vector2 newPlayerPos, const Rectangle box) {
    Vector2 resultPlayerPos = {player.x, player.y};

    resultPlayerPos.x = newPlayerPos.x;
    resultPlayerPos.y = newPlayerPos.y;
    // resultPlayerPos.x = 200.0f;
    // resultPlayerPos.y = 300.0f;

    return resultPlayerPos;
}

#define PLAYER_SPEED 250.0f

int main() {
    init();
    InitWindow(1280, 720, "Collisions");
    SetTargetFPS(60);

    Rectangle player = {GetScreenWidth() / 4.0f * 3.0f - 20.0f, GetScreenHeight() / 4.0f * 3.0f - 20.0f, 40.0f, 40.0f};
    Rectangle box = {GetScreenWidth() / 4.0f - 20.0f, GetScreenHeight() / 4.0f - 20.0f, 100.0f, 100.0f};

    while (!WindowShouldClose()) {
        Vector2 targetPlayerPos = {GetMouseX() - player.width / 2.0f, GetMouseY() - player.height / 2.0f};
        Vector2 newPlayerPos = calculateNewPlayerPos(player, targetPlayerPos, box);
        if (IsKeyDown(KEY_A))
            player.x -= PLAYER_SPEED * GetFrameTime();
        if (IsKeyDown(KEY_D))
            player.x += PLAYER_SPEED * GetFrameTime();
        if (IsKeyDown(KEY_W))
            player.y -= PLAYER_SPEED * GetFrameTime();
        if (IsKeyDown(KEY_S))
            player.y += PLAYER_SPEED * GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleRec(box, BLUE);
        DrawRectangleRec(player, RED);
        DrawRectangleLinesEx({newPlayerPos.x, newPlayerPos.y, player.width, player.height}, 2, GREEN);
        DrawLineEx(
            {player.x + player.width / 2.0f, player.y + player.height / 2.0f},
            {targetPlayerPos.x + player.width / 2.0f, targetPlayerPos.y + player.height / 2.0f},
            2, GREEN
        );
        EndDrawing();
    }

    // Engine::Game* game = new Engine::Game(init());
    // while (!game->ShouldClose())
    //     game->Update();
    // delete game;
    return 0;
}
