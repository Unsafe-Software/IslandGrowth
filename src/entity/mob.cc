#include "mob.hh"

namespace Engine {
    Mob::Mob(World* world) : Entity(world) {
        this->health = 100;
        this->world = world;
    }

    Mob::~Mob() {}

    void Mob::Update(bool debug) {
        this->updatePosition(debug);
    }

    void Mob::Draw() {
        DrawRectangleRec({this->bounds.x * 16.0f, this->bounds.y * 16.0f, this->bounds.width, this->bounds.height}, RED);
        // LOG(INFO) << "Drawing mob at " << this->bounds.x << ", " << this->bounds.y;
    }
}
