#pragma once

#include <raylib.h>
#include <glog/logging.h>

#include "entity.hh"

namespace Engine {
    class Mob : public Entity {
    private:
        int health;

    public:
        Mob(World* world);
        ~Mob();

        void Update(bool debug = false) override;
        void Draw() override;
    };
}
