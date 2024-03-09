#ifndef INIT_C
#define INIT_C

#include <string>

#include <yaml-cpp/yaml.h>
#include <glog/logging.h>
#include <raylib.h>

void initWindow(YAML::Node config) {
    InitWindow(
        (config["window"]["window"] ? config["window"]["width"].as<int>() : 1280),
        (config["window"]["window"] ? config["window"]["height"].as<int>() : 720),
        (config["window"]["window"] ? config["window"]["title"].as<std::string>().c_str() : "Island Growth")
    );
    SetTargetFPS(
        (config["window"]["fps"] ? config["window"]["fps"].as<int>() : 30)
    );
    LOG(INFO) << "Window initialized";
}

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
    initWindow(config);
    return config;
}

YAML::Node init(std::string configPath) {
    YAML::Node config = YAML::LoadFile(configPath);
    initLogging(config);
    initWindow(config);
    return config;
}

YAML::Node init() {
    YAML::Node config = YAML::LoadFile("data/config.yaml");
    initLogging(config);
    initWindow(config);
    return config;
}

#endif // INIT_C
