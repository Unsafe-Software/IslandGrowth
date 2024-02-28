#pragma once

#include <raylib.h>
#include <glog/logging.h>

namespace Engine {
    class Entity {
    protected:
        Rectangle bounds;
        Vector2 velocity;
        bool gravity;

        void updatePosition();

    public:
        Entity();
        virtual ~Entity();

        virtual void Update();
    };
}
