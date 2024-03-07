#include "world.hh"

namespace Engine {
    World::World(std::string path) {
        this->tiles = {};
        this->width = 0;
        this->height = 0;

        if (!std::__fs::filesystem::exists(path))
            LOG(FATAL) << "Worldchunk \"" << path << "\" does not exist";
        std::ifstream f(path);
        json data = json::parse(f);
        f.close();
        this->path = path;

        if (data.is_null())
            LOG(FATAL) << "Worldchunk \"" << path << "\" is empty";
        
        if (data["title"].is_null())
            LOG(FATAL) << "Worldchunk \"" << path << "\" has no title";
        this->title = data["title"];

        if (data["width"].is_null())
            LOG(FATAL) << "Worldchunk \"" << path << "\" has no width";
        this->width = data["width"];

        if (data["height"].is_null())
            LOG(FATAL) << "Worldchunk \"" << path << "\" has no height";
        this->height = data["height"];

        if (data["data"].is_null())
            LOG(FATAL) << "Worldchunk \"" << path << "\" has no data";
        if (data["data"].size() != this->width * this->height)
            LOG(FATAL) << "Worldchunk \"" << path << "\" has invalid data size";
        for (auto& tile : data["data"]) {
            this->tiles.push_back(tile.get<int>());
        }

        LOG(INFO) << "Worldchunk \"" << this->title << "\" (\"" << path << "\") loaded";
    }

    World::~World() {
        this->tiles.clear();
        LOG(INFO) << "Worldchunk \"" << this->path << "\" unloaded";
    }

    void World::Check() {
        if (this->width <= 0)
            LOG(FATAL) << "Worldchunk \"" << this->path << "\" check failed: has invalid width";
        if (this->height <= 0)
            LOG(FATAL) << "Worldchunk \"" << this->path << "\" check failed: has invalid height";
        if (this->title.empty())
            LOG(FATAL) << "Worldchunk \"" << this->path << "\" check failed: has invalid title";
        if (this->tiles.size() != this->width * this->height)
            LOG(FATAL) << "Worldchunk \"" << this->path << "\" check failed: has invalid data size";
    }

    int World::GetTile(int x, int y) {
        if (x < 0 || x  >= this->width || y < 0 || y >= this->height) {
            LOG(ERROR) << "Worldchunk \"" << this->path << "\" get tile failed: out of bounds (" << x << "x " << y << "y), returning -1";
            return -1;
        }
        return this->tiles[y * this->width + x];
    }

    void World::SetTile(int x, int y, int tile) {
        if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
            LOG(ERROR) << "Worldchunk \"" << this->path << "\" set tile failed: out of bounds (" << x << "x " << y << "y), returning";
            return;
        }
        this->tiles[y * this->width + x] = tile;
    }

    int World::GetWidth() {
        return this->width;
    }

    int World::GetHeight() {
        return this->height;
    }

    std::string World::GetTitle() {
        return this->title;
    }

    std::string World::GetPath() {
        return this->path;
    }
}
