#include "tilemap.hh"

namespace Engine {
    namespace Graphics {
        Tilemap::Tilemap(std::string path) {
            this->Load(path);
        }

        Tilemap::~Tilemap() {
            this->tiles.clear();
            LOG(INFO) << "Tilemap \"" << this->path << "\" unloaded";
        }

        void Tilemap::Load(std::string path) {
            this->tiles = {};

            if (!std::__fs::filesystem::exists(path))
                LOG(FATAL) << "Worldchunk \"" << path << "\" does not exist";
            std::ifstream f(path);
            json data = json::parse(f);
            f.close();
            this->path = path;

            if (data.is_null())
                LOG(FATAL) << "Tilemap \"" << path << "\" is empty";
            if (data["texture"].is_null())
                LOG(FATAL) << "Tilemap \"" << path << "\" has no texture";
            this->texture = LoadTexture(data["texture"].get<std::string>().c_str());
            for (auto& tile : data["tiles"]) {
                Tile t = {};
                if (tile["x"].is_null())
                    LOG(FATAL) << "Tilemap \"" << path << "\"'s tile has no x";
                t.x = tile["x"];
                if (tile["y"].is_null())
                    LOG(FATAL) << "Tilemap \"" << path << "\"'s tile has no y";
                t.y = tile["y"];
                if (tile["width"].is_null())
                    LOG(FATAL) << "Tilemap \"" << path << "\"'s tile has no width";
                t.width = tile["width"];
                if (tile["height"].is_null())
                    LOG(FATAL) << "Tilemap \"" << path << "\"'s tile has no height";
                t.height = tile["height"];
                this->tiles.push_back(t);
            }

            LOG(INFO) << "Tilemap \"" << this->path << "\" loaded";
        }

        Rectangle Tilemap::GetTile(int id) {
            if (id < 0 || id >= this->tiles.size()) {
                LOG(FATAL) << "Tilemap \"" << this->path << "\" get tile failed: out of bounds (" << id << "id)";
            }
            return {
                (float)this->tiles[id].x,
                (float)this->tiles[id].y,
                (float)this->tiles[id].width,
                (float)this->tiles[id].height
            };
        }

        Texture2D Tilemap::GetTexture() {
            return this->texture;
        }
    }
}

