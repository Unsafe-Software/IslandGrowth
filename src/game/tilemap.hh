#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "raylib.h"
#include <glog/logging.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Engine {
    namespace Graphics {
        struct Tile {
            int x;
            int y;
            int width;
            int height;
        };

        class Tilemap {
        private:
            std::vector<Tile> tiles;
            Texture2D texture;
            std::string path;

        public:
            Tilemap(std::string path);
            ~Tilemap();

            void Load(std::string path);

            Rectangle GetTile(int id);
            Texture2D GetTexture();
        };
    }
}

