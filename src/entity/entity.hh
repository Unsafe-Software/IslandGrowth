#pragma once

#include <raylib.h>
#include <glog/logging.h>

#include "../world/world.hh"

namespace Engine {
    class Entity {
    public:
        Rectangle bounds;
        Vector2 velocity;
        World* world;

        Entity(World* world);
        virtual ~Entity();

        virtual void Update();
        virtual void Draw();
        void updatePosition();
        void resolveCollisions();
    };
}
