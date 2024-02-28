#include "entity.hh"

namespace Engine {
    Entity::Entity() {
        this->bounds = {0.0f, 0.0f, 1.0f, 1.0f};
        this->velocity = {0.0f, 0.0f};
        this->gravity = true;
    }

    Entity::~Entity() {}

    void Entity::Update() {}

    void Entity::updatePosition() {
        this->bounds.x += this->velocity.x;
        this->bounds.y += this->velocity.y;
    }
}
