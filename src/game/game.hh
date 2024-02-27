#pragma once

#include <raylib.h>
#include <raymath.h>
#include <yaml-cpp/yaml.h>
#include <glog/logging.h>

class Game {
private:
    YAML::Node config;
    Camera2D camera;
    Texture2D tilemap;
    bool debug;
    int targetFPS;
    Vector2 camera_target;

    void updateCamera();

    void drawGame();
    void drawUI();
    void drawDebug();

public:
    Game(YAML::Node config);
    ~Game();

    void Update();
    bool ShouldClose();
};
