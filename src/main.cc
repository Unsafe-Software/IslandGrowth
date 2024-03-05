#include "init.c"
#include "game/game.hh"

#include "entity/entity.hh"
#include "entity/mob.hh"

#include <raylib.h>

Vector2 calculateNewPlayerPos(const Rectangle player, const Vector2 newPlayerPos, const Rectangle box) {
    Vector2 resultPlayerPos = {newPlayerPos.x, newPlayerPos.y};
    DrawLineEx({player.x, player.y}, {newPlayerPos.x, newPlayerPos.y}, 2, GREEN);
    Ray ray = {0};
    ray.position = (Vector3){player.x + player.width / 2.0f, player.y + player.height / 2.0f, 0.0f};
    ray.direction = Vector3Normalize(Vector3Subtract({newPlayerPos.x, newPlayerPos.y, 0.0f}, {player.x, player.y, 0.0f}));
    DrawRay(ray, RED);
    Rectangle oversizedBox = {
        box.x - player.width / 2.0f,
        box.y - player.height / 2.0f,
        box.width + player.width,
        box.height + player.height
    };
    DrawRectangleLinesEx(oversizedBox, 2, BLUE);
    RayCollision collision = GetRayCollisionBox(ray, BoundingBox{
        (Vector3){oversizedBox.x, oversizedBox.y, 0.0f},
        (Vector3){oversizedBox.x + oversizedBox.width, oversizedBox.y + oversizedBox.height, 0.0f}
    });
    if (collision.hit == 1) {
        float maxDistanceX = Vector2Distance(
            {player.x + player.width / 2.0f, player.y + player.height / 2.0f},
            {newPlayerPos.x + player.width / 2.0f, player.y + player.height / 2.0f}
        );
        float DistanceX = Vector2Distance(
            {player.x + player.width / 2.0f, player.y + player.height / 2.0f},
            {collision.point.x, player.y + player.height / 2.0f}
        );
        LOG(INFO) << "DistanceX: " << DistanceX << " maxDistanceX: " << maxDistanceX;
        if (DistanceX == 0) {
            Ray rayHor = {0};
            rayHor.position = (Vector3){player.x + player.width / 2.0f, player.y + player.height / 2.0f, 0.0f};
            rayHor.direction = Vector3Normalize(Vector3Subtract({newPlayerPos.x, 0.0f, 0.0f}, {player.x, 0.0f, 0.0f}));
            DrawRay(rayHor, BLUE);
            RayCollision collisionHor = GetRayCollisionBox(rayHor, BoundingBox{
                (Vector3){oversizedBox.x, oversizedBox.y, 0.0f},
                (Vector3){oversizedBox.x + oversizedBox.width, oversizedBox.y + oversizedBox.height, 0.0f}
            });
            if (collisionHor.hit == 1) {
                float maxDistanceHor = Vector2Distance(
                    {player.x + player.width / 2.0f, player.y + player.height / 2.0f},
                    {newPlayerPos.x + player.width / 2.0f, player.y + player.height / 2.0f}
                );
                float DistanceHor = Vector2Distance(
                    {player.x + player.width / 2.0f, player.y + player.height / 2.0f},
                    {collisionHor.point.x, player.y + player.height / 2.0f}
                );
                if (DistanceHor < maxDistanceHor)
                    resultPlayerPos.x = collisionHor.point.x - player.width / 2.0f;
            }
        } else if (DistanceX < maxDistanceX)
            resultPlayerPos.x = collision.point.x - player.width / 2.0f;
        
        float maxDistanceY = Vector2Distance(
            {player.x + player.width / 2.0f, player.y + player.height / 2.0f},
            {player.x + player.width / 2.0f, newPlayerPos.y + player.height / 2.0f}
        );
        float DistanceY = Vector2Distance(
            {player.x + player.width / 2.0f, player.y + player.height / 2.0f},
            {player.x + player.width / 2.0f, collision.point.y}
        );
        LOG(INFO) << "DistanceY: " << DistanceY << " maxDistanceY: " << maxDistanceY;
        if (DistanceY == 0) {
            Ray rayVer = {0};
            rayVer.position = (Vector3){player.x + player.width / 2.0f, player.y + player.height / 2.0f, 0.0f};
            rayVer.direction = Vector3Normalize(Vector3Subtract({0.0f, newPlayerPos.y, 0.0f}, {0.0f, player.y, 0.0f}));
            DrawRay(rayVer, BLUE);
            RayCollision collisionVer = GetRayCollisionBox(rayVer, BoundingBox{
                (Vector3){oversizedBox.x, oversizedBox.y, 0.0f},
                (Vector3){oversizedBox.x + oversizedBox.width, oversizedBox.y + oversizedBox.height, 0.0f}
            });
            if (collisionVer.hit == 1) {
                float maxDistanceVer = Vector2Distance(
                    {player.x + player.width / 2.0f, player.y + player.height / 2.0f},
                    {player.x + player.width / 2.0f, newPlayerPos.y + player.height / 2.0f}
                );
                float DistanceVer = Vector2Distance(
                    {player.x + player.width / 2.0f, player.y + player.height / 2.0f},
                    {player.x + player.width / 2.0f, collisionVer.point.y}
                );
                if (DistanceVer < maxDistanceVer)
                    resultPlayerPos.y = collisionVer.point.y - player.height / 2.0f;
            }
        } else if (DistanceY < maxDistanceY)
            resultPlayerPos.y = collision.point.y - player.height / 2.0f;

        // float maxDistance = Vector2Distance(
        //     {player.x + player.width / 2.0f, player.y + player.height / 2.0f},
        //     {newPlayerPos.x + player.width / 2.0f, newPlayerPos.y + player.height / 2.0f}
        // );
        // float Distance = Vector2Distance(
        //     {player.x + player.width / 2.0f, player.y + player.height / 2.0f},
        //     {collision.point.x, collision.point.y}
        // );
        // if (Distance < maxDistance)
        //     resultPlayerPos = {collision.point.x - player.width / 2.0f, collision.point.y - player.height / 2.0f};
    }

    return resultPlayerPos;
}

#define PLAYER_SPEED 250.0f

int main() {
    init();
    InitWindow(1280, 720, "Collisions");
    SetTargetFPS(60);

    Rectangle player = {GetScreenWidth() / 4.0f * 3.0f - 20.0f, GetScreenHeight() / 4.0f * 3.0f - 20.0f, 40.0f, 80.0f};
    Rectangle box = {GetScreenWidth() / 4.0f - 20.0f, GetScreenHeight() / 4.0f - 20.0f, 200.0f, 100.0f};
    Rectangle box2 = {GetScreenWidth() / 4.0f - 20.0f - 5.0f, GetScreenHeight() / 4.0f - 20.0f + 120.0f, 20.0f, 200.0f};

    while (!WindowShouldClose()) {
        Vector2 offset = {0.0f, 0.0f};
        if (IsKeyDown(KEY_A))
            offset.x -= PLAYER_SPEED * GetFrameTime();
        if (IsKeyDown(KEY_D))
            offset.x += PLAYER_SPEED * GetFrameTime();
        if (IsKeyDown(KEY_W))
            offset.y -= PLAYER_SPEED * GetFrameTime();
        if (IsKeyDown(KEY_S))
            offset.y += PLAYER_SPEED * GetFrameTime();
        if (offset.x != 0 && offset.y != 0) {
            offset.x = offset.x / 1.4142;
            offset.y = offset.y / 1.4142;
        }
        Vector2 targetPlayerPos = {player.x + offset.x, player.y + offset.y};
        Vector2 newPlayerPos = calculateNewPlayerPos(player, targetPlayerPos, box);
        newPlayerPos = calculateNewPlayerPos(player, newPlayerPos, box2);
        player.x = newPlayerPos.x;
        player.y = newPlayerPos.y;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleRec(box, BLUE);
        DrawRectangleRec(box2, BLUE);
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
