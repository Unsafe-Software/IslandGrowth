cmake_minimum_required(VERSION 3.8.0)
project(IslandGrowth VERSION 0.0.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)

# --- Data ---
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

# --- Libraries ---
include(FetchContent)
# Glog
FetchContent_Declare(
  glog
  GIT_REPOSITORY "https://github.com/google/glog.git"
  GIT_TAG "v0.6.0"
)
FetchContent_MakeAvailable(glog)
# Raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
  GIT_TAG "5.0"
)
FetchContent_MakeAvailable(raylib)
# Json
FetchContent_Declare(
  json
  GIT_REPOSITORY "https://github.com/nlohmann/json.git"
  GIT_TAG "v3.11.3"
)
FetchContent_MakeAvailable(json)
# YAML 
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY "https://github.com/jbeder/yaml-cpp.git"
  GIT_TAG "0.8.0"
)
FetchContent_GetProperties(yaml-cpp)
if(NOT yaml-cpp_POPULATED)
  message(STATUS "Fetching yaml-cpp...")
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()

# --- Executables ---
file(GLOB Sources src/*.cc src/game/*.cc src/world/*.cc)
add_executable("${PROJECT_NAME}" ${Sources})
target_link_libraries("${PROJECT_NAME}"
  yaml-cpp::yaml-cpp raylib
  glog::glog nlohmann_json::nlohmann_json
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPACK)
