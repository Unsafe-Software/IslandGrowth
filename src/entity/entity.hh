#pragma once

#include <vector>

#include <raylib.h>
#include <raymath.h>
#include <glog/logging.h>

#include "../world/world.hh"

namespace Engine {
    class Entity {
    public:
        Rectangle bounds;
        Vector2 velocity;
        World* world;
        bool noClip;

        Entity(World* world, bool noClip = false);
        virtual ~Entity();

        virtual void Update(bool debug = false);
        virtual void Draw();
        void updatePosition(bool debug);
        Vector2 ResolveCollisionBox(const Rectangle player, const Vector2 newPlayerPos, const Rectangle box, bool debug);
        void ResolveWorldCollisions(const Vector2 newPlayerPos, bool debug);
    };
}
