#pragma once

#include <raylib.h>
#include <yaml-cpp/yaml.h>
#include <glog/logging.h>

class Game {
private:
    YAML::Node config;
    Camera2D camera;
    Texture2D tilemap;
    bool debug;
    int targetFPS;

public:
    Game(YAML::Node config);
    ~Game();

    void Update();
    bool ShouldClose();
};
