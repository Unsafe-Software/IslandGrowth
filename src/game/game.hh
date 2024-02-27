#pragma once

#include <raylib.h>
#include <raymath.h>
#include <yaml-cpp/yaml.h>
#include <glog/logging.h>

#include "../world/world.hh"
#include "tilemap.hh"

namespace Engine {
    class Game {
    private:
        YAML::Node config;
        Camera2D camera;
        Engine::Graphics::Tilemap* tilemap;
        bool debug;
        int targetFPS;
        Vector2 camera_target;
        Engine::World* current_world;
        float speed;

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
}
