#include "entity.hh"

namespace Engine {
    Entity::Entity(World* world) {
        this->bounds = {0.0f, 0.0f, 16.0f, 16.0f};
        this->velocity = {0.0f, 0.0f};
        this->world = world;
    }

    Entity::~Entity() {}

    void Entity::Update() {}

    void Entity::Draw() {}

    void Entity::updatePosition() {
        this->bounds.x += this->velocity.x;
        this->bounds.y += this->velocity.y;
    }

    void addTile(std::vector<Rectangle> &rects, World* world, float x, float y, int type) {
        if (world->GetTile(x, y) == type) {
            rects.push_back((Rectangle){x - 0.01f, y - 0.01f, 1.0f + 0.01f, 1.0f + 0.01f});
            DrawRectangle((x) * 16, (y) * 16, 16.0f, 16.0f, YELLOW);
        }
    }

    void Entity::resolveCollisions() {
    }
}
