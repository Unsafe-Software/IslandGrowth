#pragma once

#include <raylib.h>
#include <glog/logging.h>

#include "entity.hh"

namespace Engine {
    class Player : public Entity {
    private:
        int health;

    public:
        Player(World* world);
        ~Player();

        void Update(bool debug = false) override;
        void Draw() override;
    };
}
