#pragma once

#include <raylib.h>
#include <yaml-cpp/yaml.h>
#include <glog/logging.h>

#include "../scenes.hh"

namespace Engine {
    class Menu {
    private:
        YAML::Node config;

    public:
        Menu(YAML::Node config);
        ~Menu();

        int Update();
    };
}
