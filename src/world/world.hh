#pragma once

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

#include <glog/logging.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Engine {
    class World {
    private:
        std::vector<int> tiles;
        std::string path;
        std::string title;
        int width;
        int height;

    public:
        World(std::string path);
        ~World();

        void Check();
        void Update();

        int GetTile(int x, int y);
        void SetTile(int x, int y, int tile);
        int GetWidth();
        int GetHeight();
        std::string GetTitle();
        std::string GetPath();
    };
}
