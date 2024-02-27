#ifndef INIT_C
#define INIT_C

#include <string>

#include <yaml-cpp/yaml.h>
#include <glog/logging.h>
#include <raylib.h>

bool getDebug(YAML::Node config) {
    return (config["debug"] ? config["debug"].as<bool>() : false);
}

int getTargetFPS(YAML::Node config) {
    return (config["window"]["fps"] ? config["window"]["fps"].as<int>() : 30);
}

bool getRaylibDebug(YAML::Node config) {
    return (config["raylib_debug"] ? config["raylib_debug"].as<bool>() : false);
}

void initLogging(YAML::Node config) {
    FLAGS_alsologtostderr = getDebug(config);
    google::InitGoogleLogging("IslandGrowth");
    if (config["raylib_debug"]) {
        SetTraceLogLevel(config["raylib_debug"].as<bool>() ? LOG_ALL : LOG_NONE);
    }
}

YAML::Node init(YAML::Node config) {
    initLogging(config);
    return config;
}

YAML::Node init(std::string configPath) {
    YAML::Node config = YAML::LoadFile(configPath);
    initLogging(config);
    return config;
}

YAML::Node init() {
    YAML::Node config = YAML::LoadFile("data/config.yaml");
    initLogging(config);
    return config;
}

#endif // INIT_C
