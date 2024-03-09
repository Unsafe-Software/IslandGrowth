#pragma once

#include <vector>

#include <raylib.h>
#include <raymath.h>
#include <yaml-cpp/yaml.h>
#include <glog/logging.h>

#include "../world/world.hh"
#include "../entity/entity.hh"
#include "../entity/mob.hh"
#include "../entity/player.hh"
#include "../scenes.hh"
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
        Player player;

        void updateCamera();

        void drawGame();
        void drawUI();
        void drawDebug();

    public:
        Game(YAML::Node config);
        ~Game();

        int Update();
        bool ShouldClose();
    };
}
