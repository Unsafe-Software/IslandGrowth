#include "player.hh"

namespace Engine {
    Player::Player(World* world) : Entity(world) {
        this->health = 100;
        this->world = world;
    }

    Player::~Player() {}

    void Player::Update(bool debug) {
        this->updatePosition(debug);
    }

    void Player::Draw() {
        DrawRectangleRec({this->bounds.x * 16.0f, this->bounds.y * 16.0f, this->bounds.width, this->bounds.height}, BLUE);
    }
}
